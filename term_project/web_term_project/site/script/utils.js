// @ts-check

/** @typedef {import('./typedef').Point } Point */
/** @typedef {import('./typedef').RGBA } RGBA */
/** @typedef {{ start: Point, end: Point, color: RGBA }} LineInfo */

class Shaders {
    /** @type {Map<string, WebGLProgram>} */
    static shader_map = new Map;

    /**
     * @param {string} name 
     * @param {WebGLProgram} shader 
     */
    static setShader(name, shader) {
        Shaders.shader_map.set(name, shader);
    }

    /**
     * @param {string} name 
     */
    static getShader(name) {
        return Shaders.shader_map.get(name);
    }
}

/**
 * @param {WebGL2RenderingContext} gl 
 * @param {number} type 
 * @param {string} source 
 */
function loadShader(gl, type, source) {
    const shader = gl.createShader(gl.VERTEX_SHADER);
    gl.shaderSource(shader, source);
    gl.compileShader(shader);

    if(!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        alert(`Init ${(type == gl.VERTEX_SHADER ? 'vertex shader' : 'fragment shader')} failed:` +
                gl.getShaderInfoLog(shader));
        gl.deleteShader(shader);
        return null;
    }

    return shader;
}

/**
 * @param {WebGL2RenderingContext} gl 
 * @param {string} name
 * @param {string} vertex
 * @param {string} fragment
 */
function addShader(gl, name, vertex, fragment) {
    const vertex_shader = loadShader(gl, gl.VERTEX_SHADER, vertex);
    const fragment_shader = loadShader(gl, gl.FRAGMENT_SHADER, fragment);

    const shader_program = gl.createProgram();
    gl.attachShader(shader_program, vertex_shader);
    gl.attachShader(shader_program, fragment_shader);
    gl.linkProgram(shader_program);

    gl.deleteShader(vertex_shader);
    gl.deleteShader(fragment_shader);
    if(!gl.getProgramParameter(shader_program, gl.LINK_STATUS)) {
        alert(`Init shader program failed:` + gl.getProgramInfoLog(shader_program));
        gl.deleteProgram(shader_program);
        return;
    }

    Shaders.setShader(name, shader_program);
}

/**
 * @param {WebGL2RenderingContext} gl 
 * @param {LineInfo[]} line_infos 
 */
function drawLines(gl, line_infos) {
    let data = [];
    line_infos.forEach(
        /** @param {LineInfo} info */
        function(info) {
            data.concat(info.start.data)
                .concat(info.end.data);
        }
    );

    const buffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(data), gl.STATIC_DRAW);

    gl.vertexAttribPointer(0, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(0);

    gl.useProgram(Shaders.getShader('line'));
    gl.drawArrays(gl.LINES, 0, line_infos.length);
    gl.deleteBuffer(buffer);
}

export {
    
    addShader,
    drawLines
    /** @type {Point} */
}