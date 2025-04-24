extends Spatial

var singleNote = load("res://assets/singleNote.tscn")
var testCut = load("res://assets/testCut.tscn")

var vr_mode = false

var cutter
var cutterKinematic

var pos = Vector3(0,0,0)
var speed = 0.6
var cutter_speed = 5
var cut_separation_force = 1.5;

var start_cut = false
var is_cut = false

#Placeholder using random cut points and directions
var rand_val_x_1
var rand_val_y_1
var rand_val_x_2
var rand_val_y_2

var cutter_start_point = Vector3(0, 0, 0)
var cutter_target_point = Vector3(0, 0, 0)
var cutter_direction = Vector3(0, 0, 0)

func _ready():
	
	if get_parent().get_parent() != null and get_parent().get_parent().name == 'Spatial':
		vr_mode = get_parent().get_parent().vr_mode
		
	if !vr_mode:
				
		cutter = testCut.instance()
		cutterKinematic = cutter.get_node('cutterKinematic')
		get_parent().get_parent().get_node('nonVRCutters').add_child(cutter)
		cutter.translation.z = 20
		
		rand_val_x_1 = rand_range(-2,2)
		rand_val_y_1 = rand_range(-2,2)
		rand_val_x_2 = rand_range(-0.25,0.25)
		rand_val_y_2 = rand_range(-0.25,0.25)
		
		cutter_start_point = Vector3(rand_val_x_1, rand_val_y_1, 0)
		cutter_target_point = Vector3(rand_val_x_2, rand_val_y_2, 0)

func _process(delta):
	
	pos[2] += speed * delta
	translate(pos)
	
	if !vr_mode && cutter != null:
		
		if pos.z > 0.25 and !start_cut:
			
			start_cut = true
			cutter.translation = translation + cutter_start_point
			cutter.translation.z = translation.z
			cutter.rotate_x(deg2rad(-90.0))
			
			cutter_direction = translation - cutter.translation
			
			#Avoid predictablilty, so it won't try to go towards the center by default
			#cutter_direction = to_global(cutter_target_point) - cutter.translation
			
			cutter_direction = cutter_direction.normalized()
			cutter_direction.z = 0
			
		elif start_cut:
			
			cutter.translation.z = translation.z + 2.5
			var collision_info = cutterKinematic.move_and_collide(cutter_direction * cutter_speed * delta)
			
			if collision_info:
				
				if collision_info.collider == get_node("directionalNote") or collision_info.collider == get_node("allDirectionsNote"):
				
					var collision_position_local = to_local(collision_info.position)
					collision_position_local.z = 0
					
					cut_note(collision_position_local, cutter_direction)

func cut_note(cut_point, cut_direction):
	is_cut = true
	visible = false
		
	instance_and_init_note_segment(cut_point, cut_direction, false)
	#Substract the second instance so it matches the first segment
	instance_and_init_note_segment(cut_point, cut_direction, true)
	
	queue_free()
	
	if cutter != null:
		cutter.queue_free()

func instance_and_init_note_segment(cut_point, cut_direction, isSubtraction):
	
	var rigidBody 
	var intersection_box
	var impulse_force_magnitude = cut_separation_force
	
	var note_segment = singleNote.instance()

	get_parent().get_parent().get_node('singleNote').add_child(note_segment)

	note_segment.translation = translation
	note_segment.rotation = rotation
	note_segment.get_node('directionalNote').visible = get_node("directionalNote").visible
	note_segment.get_node('allDirectionsNote').visible = get_node("allDirectionsNote").visible

	intersection_box = note_segment.get_node('directionalNote/csgPolygon/intersectionBox')

	if get_node("directionalNote").visible:
		intersection_box = note_segment.get_node('directionalNote/csgPolygon/intersectionBox')
		rigidBody = note_segment.get_node('directionalNote')
	elif get_node("allDirectionsNote").visible:
		intersection_box = note_segment.get_node('directionalNote/csgPolygon/intersectionBox')
		rigidBody = note_segment.get_node('allDirectionsNote')

	if isSubtraction:
		intersection_box.set_operation(2)
		impulse_force_magnitude *= -1;

	var desiredPos = Vector3(cut_point)
	desiredPos.z = 1
	intersection_box.translation = desiredPos
	
	var rotate_z_radians = atan2(cut_direction.x, cut_direction.y)
	intersection_box.rotate_z(-(note_segment.rotation.z + rotate_z_radians))
	
	rigidBody.apply_impulse(Vector3(0,0,0), -transform.basis.x * impulse_force_magnitude)
