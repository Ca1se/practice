import { drawLines, Manage } from './utils.js';
import { Point, Rectangle, Shape } from './typedef.js';


/** @type {Shape} */
let targetItem = null;

/**
 * @param {Shape} item
 */
function setTargetItem(item) {
    if(targetItem != null) {
        targetItem.setZoomFrame(false);
    }
    targetItem = item;
    if(targetItem != null) {
        targetItem.setZoomFrame(true);
    }
}

function drawBackground() {
    /** @type {HTMLCanvasElement} */
    const canvas = $('#back-canvas')[0];
    const ctx = canvas.getContext('2d');

    ctx.fillStyle = 'white';
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    /** @type {{ start: Point, end: Point }[]} */
    let arr = [];
    let arr1 = [];
    let interval = 30;
    for(let i = 0; i < canvas.height; i += interval) {
        let t;
        if(i % 90 != 0) { t = arr; }
        else { t = arr1; }
        t.push({
            start: new Point(0, i),
            end:   new Point(canvas.width, i),
        });
    }
    for(let i = 0; i < canvas.width; i += interval) {
        let t;
        if(i % 90 != 0) { t = arr; }
        else { t = arr1; }
        t.push({
            start: new Point(i, 0),
            end:   new Point(i, canvas.height)
        });
    }
    drawLines(ctx, arr, 0.08, 'black');
    drawLines(ctx, arr1, 0.3, 'black');
}

/** @type {Shape} */
let moving_item = null;

let resizing = false;

let rotating = false;
let rotating_center = new Point(0, 0);
let rotating_prevec = new Point(0, 0);

/**
 * @param {Shape} item 
 */
function enableItem(item) {
    item.show('container');

    const wrapper = item.wrapper;
    $(wrapper).on('click', event => {
        event.stopPropagation();
        setTargetItem(item);
    });

    $(wrapper).on('mousedown', event => {
        event.stopPropagation();
        moving_item = item;
    });

    const rotate = item.rotate;
    rotate.addEventListener('mousedown', event => {
        event.stopPropagation();
        rotating_center.x = item.wrapper.getBoundingClientRect().left + item.width / 2;
        rotating_center.y = item.wrapper.getBoundingClientRect().top + item.height / 2;
        rotating_prevec.x = event.clientX - rotating_center.x;
        rotating_prevec.y = event.clientY - rotating_center.y;
        rotating = true;
    });
}

function drawRect(x, y) {
    const rect = new Rectangle(new Point(x, y), 100, 100, '#000000', false);
    enableItem(rect);
}

function drawTriangle(x, y) {

}

function drawCircle(x, y) {

}

function drawSquare(x, y) {

}

$(() => {
    drawBackground();

    const drawMethodMap = new Map;
    drawMethodMap.set(0, drawRect);
    drawMethodMap.set(1, drawTriangle);
    drawMethodMap.set(2, drawCircle);
    drawMethodMap.set(3, drawSquare);

    let aim_shape;
    $('#rect').on('dragstart', () => { aim_shape = 0; });
    $('#triangle').on('dragstart', () => { aim_shape = 1; });
    $('#circle').on('dragstart', () => { aim_shape = 2; });
    $('#square').on('dragstart', () => { aim_shape = 3; });

    const container = $('#container')[0];
    $(container).on('dragover', event => { event.preventDefault(); });
    $(container).on('drop', event => {
        drawMethodMap.get(aim_shape)(event.offsetX - 50, event.offsetY - 50);
    });
    $(container).on('click', () => { setTargetItem(null); });
    $(container).on('mouseup', () => { moving_item = null; });
    container.addEventListener('mousemove', event => {
        if(moving_item != null) {
            moving_item.update(event.movementX, event.movementY);
        }else if(resizing) {

        }else if(rotating) {
            const nowvec = new Point(event.clientX - rotating_center.x,
                                     event.clientY - rotating_center.y);
            
        }
    });
})