// @ts-check

/** @typedef {import('./typedef').Point } Point */
/** @typedef {import('./typedef').Shape } Shape */

/**
 * @param {CanvasRenderingContext2D} ctx 
 * @param {{ start: Point, end: Point }[]} line_endpoints 
 * @param {number} width 
 * @param {string} color 
 */
function drawLines(ctx, line_endpoints, width, color) {
    ctx.strokeStyle = color;
    ctx.lineWidth = width;
    ctx.beginPath();
    line_endpoints.forEach(
        /** @type {{ start: Point, end: Point }} */
        function(points) {
            ctx.moveTo(points.start.x, points.start.y);
            ctx.lineTo(points.end.x, points.end.y);
        }
    );
    ctx.stroke();
}

export {
    drawLines
}