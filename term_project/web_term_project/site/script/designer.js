import { drawLines } from './utils.js';
import { Circle, Hexagon, Point, Rectangle, Shape, Triangle } from './typedef.js';


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
let titem = null;

let moving   = false;
let scaling = false;
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
        titem = item;
        moving = true;
    });

    const rotate = item.rotate;
    $(rotate).on('mousedown', event => {
        event.stopPropagation();
        titem = item;
        rotating_center.x = item.wrapper.getBoundingClientRect().left + item.width / 2;
        rotating_center.y = item.wrapper.getBoundingClientRect().top + item.height / 2;
        rotating_prevec.x = event.clientX - rotating_center.x;
        rotating_prevec.y = event.clientY - rotating_center.y;
        rotating = true;
    });

    const scale = item.scale;
    $(scale).on('mousedown', event => {
        event.stopPropagation();
        titem = item;
        scaling = true;
    });
}

function drawRect(x, y) {
    const rect = new Rectangle(new Point(x, y), 100, 100, '#000000', false);
    enableItem(rect);
}

function drawTriangle(x, y) {
    const triagnle = new Triangle(new Point(x, y), 100, 87, '#000000', false);
    enableItem(triagnle);
}

function drawCircle(x, y) {
    const circle = new Circle(new Point(x, y), 100, 100, '#000000', false);
    enableItem(circle);
}

function drawHexagon(x, y) {
    const hexagon = new Hexagon(new Point(x, y), 100, 87, '#000000', false);
    enableItem(hexagon);
}

/**
 * @param {Point} vec 
 */
function squareNorm(vec) {
    return Math.sqrt(vec.x * vec.x + vec.y * vec.y);
}

$(() => {
    drawBackground();

    const drawMethodMap = new Map;
    drawMethodMap.set(0, drawRect);
    drawMethodMap.set(1, drawTriangle);
    drawMethodMap.set(2, drawCircle);
    drawMethodMap.set(3, drawHexagon);

    let aim_shape = -1;
    $('#rect').on('dragstart', () => { aim_shape = 0; });
    $('#triangle').on('dragstart', () => { aim_shape = 1; });
    $('#circle').on('dragstart', () => { aim_shape = 2; });
    $('#hexagon').on('dragstart', () => { aim_shape = 3; });

    const container = $('#container')[0];
    $(container).on('dragover', event => { event.preventDefault(); });
    $(container).on('drop', event => {
        if(aim_shape != -1) {
            drawMethodMap.get(aim_shape)(event.offsetX - 50, event.offsetY - 50);
            aim_shape = -1;
        }
    });
    $(container).on('click', () => { setTargetItem(null); });
    $(container).on('mouseup', () => { moving = false; scaling = false; rotating = false; });
    container.addEventListener('mousemove', event => {
        if(moving) {
            titem.update({ start_offset: new Point(event.movementX, event.movementY) });
        }else if(scaling) {
            titem.update({ scale_offset: new Point(event.movementX, event.movementY) });
        }else if(rotating) {
            const nowvec = new Point(event.clientX - rotating_center.x,
                                     event.clientY - rotating_center.y);
            if(Math.abs(rotating_prevec.x * nowvec.x + rotating_prevec.y * nowvec.y)
                     / (squareNorm(rotating_prevec) * squareNorm(nowvec)) <= 0.998) {
                let deg = 5;
                if(rotating_prevec.x * nowvec.y - rotating_prevec.y * nowvec.x < 0) {
                    deg = -5;
                }
                titem.update({ rotate: deg });
                rotating_prevec = nowvec;
            }
        }
    });
})