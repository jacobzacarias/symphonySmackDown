// // Get the WebGL context
// const canvas = document.getElementById('canvas');
// const gl = canvas.getContext('webgl');

// // Define vertex shader
// const vertexShaderSource = `
//     attribute vec3 position;
//     attribute vec2 texCoord;
//     attribute vec3 normal;
    
//     uniform mat4 modelViewMatrix;
//     uniform mat4 projectionMatrix;
//     uniform mat4 normalMatrix;
    
//     varying vec2 vTexCoord;
//     varying vec3 vNormal;
    
//     void main() {
//         gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
//         vTexCoord = texCoord;
//         vNormal = mat3(normalMatrix) * normal;
//     }
// `;

// // Define fragment shader
// const fragmentShaderSource = `
//     precision mediump float;
    
//     uniform vec3 lightDirection;
//     uniform sampler2D texture;
    
//     varying vec2 vTexCoord;
//     varying vec3 vNormal;
    
//     void main() {
//         vec3 lightColor = vec3(1.0, 1.0, 1.0);
//         vec3 ambientColor = vec3(0.2, 0.2, 0.2);
        
//         vec3 N = normalize(vNormal);
//         float intensity = max(dot(N, lightDirection), 0.0);
//         vec3 diffuse = lightColor * intensity;
//         vec3 ambient = ambientColor;
        
//         gl_FragColor = texture2D(texture, vTexCoord) * vec4(diffuse + ambient, 1.0);
//     }
// `;

// // Compile and link shaders
// const vertexShader = gl.createShader(gl.VERTEX_SHADER);
// gl.shaderSource(vertexShader, vertexShaderSource);
// gl.compileShader(vertexShader);

// const fragmentShader = gl.createShader(gl.FRAGMENT_SHADER);
// gl.shaderSource(fragmentShader, fragmentShaderSource);
// gl.compileShader(fragmentShader);

// const program = gl.createProgram();
// gl.attachShader(program, vertexShader);
// gl.attachShader(program, fragmentShader);
// gl.linkProgram(program);
// gl.useProgram(program);

// // Create vertex buffer
// const vertexBuffer = gl.createBuffer();
// gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);

// const vertices = [
//     // Vertex positions (x, y, z)
//     -1, -1, 0,
//     1, -1, 0,
//     -1, 1, 0,
//     1, 1, 0,
    
//     // Texture coordinates (s, t)
//     0, 0,
//     1, 0,
//     0, 1,
//     1, 1,
    
//     // Vertex normals (x, y, z)
//     0, 0, 1,
//     0, 0, 1,
//     0, 0, 1,
//     0, 0, 1
// ];

// // Function to compile a shader
// function compileShader(gl, source, type) {
//     const shader = gl.createShader(type);
//     gl.shaderSource(shader, source);
//     gl.compileShader(shader);

//     if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
//         console.error("An error occurred compiling the shaders: " + gl.getShaderInfoLog(shader));
//         gl.deleteShader(shader);
//         return null;
//     }

//     return shader;
// }

// // Function to link shaders into a program
// function linkProgram(gl, vertexShader, fragmentShader) {
//     const program = gl.createProgram();
//     gl.attachShader(program, vertexShader);
//     gl.attachShader(program, fragmentShader);
//     gl.linkProgram(program);

//     if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
//         console.error("Unable to initialize the shader program: " + gl.getProgramInfoLog(program));
//         return null;
//     }

//     return program;
// }

// // Function to create and bind a vertex buffer
// function createVertexBuffer(gl, data) {
//     const vertexBuffer = gl.createBuffer();
//     gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
//     gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(data), gl.STATIC_DRAW);
//     return vertexBuffer;
// }

// // Function to enable and specify vertex attributes
// function setVertexAttrib(gl, program, attributeLocation, size, type, stride, offset) {
//     const attribLocation = gl.getAttribLocation(program, attributeLocation);
//     gl.enableVertexAttribArray(attribLocation);
//     gl.vertexAttribPointer(attribLocation, size, type, false, stride, offset);
// }

// // Function to set uniform matrix and vector values
// function setUniformMatrix4fv(gl, program, uniformLocation, value) {
//     gl.uniformMatrix4fv(uniformLocation, false, value);
// }

// gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

// // Specify vertex attributes
// const positionAttribLocation = gl.getAttribLocation(program, 'position');
// gl.enableVertexAttribArray(positionAttribLocation);
// gl.vertexAttribPointer(positionAttribLocation, 3, gl.FLOAT, false, 0, 0);

// const texCoordAttribLocation = gl.getAttribLocation(program, 'texCoord');
// gl.enableVertexAttribArray(texCoordAttribLocation);
// gl.vertexAttribPointer(texCoordAttribLocation, 2, gl.FLOAT, false, 0, 4 * 3 * 4); // 4 floats per vertex, 3 vertices per triangle, 4 bytes per float

// const normalAttribLocation = gl.getAttribLocation(program, 'normal');
// gl.enableVertexAttribArray(normalAttribLocation);
// gl.vertexAttribPointer(normalAttribLocation, 3, gl.FLOAT, false, 0, 4 * (3 + 2) * 4); // 4 floats per vertex, 3 vertices per triangle, 2 texture coordinates per vertex, 4 bytes per float

// // Set uniforms
// const modelViewMatrixUniformLocation = gl.getUniformLocation(program, 'modelViewMatrix');
// const projectionMatrixUniformLocation = gl.getUniformLocation(program, 'projectionMatrix');
// const normalMatrixUniformLocation = gl.getUniformLocation(program, 'normalMatrix');
// const lightDirectionUniformLocation = gl.getUniformLocation(program, 'lightDirection');

// gl.uniformMatrix4fv(modelViewMatrixUniformLocation, false, modelViewMatrix);
// gl.uniformMatrix4fv(projectionMatrixUniformLocation, false, projectionMatrix);
// gl.uniformMatrix4fv(normalMatrixUniformLocation, false, normalMatrix);
// gl.uniform3fv(lightDirectionUniformLocation, lightDirection);

// // Draw
// gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
