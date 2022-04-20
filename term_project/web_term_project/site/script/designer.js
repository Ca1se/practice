// @ts-check

import { addShader, drawLines } from "./utils";
import { kLineVsSource, kLineFsSource} from './shader_source';

function main() {
    /** @type {HTMLCanvasElement} */
    const canvas = document.querySelector('.glcanvas');
    const gl = canvas.getContext('webgl2');

    addShader(gl, 'line', kLineVsSource, kLineFsSource);

    /** @type {import("./utils").LineInfo} */
    const line = {
    };

    drawLines(gl, )
}