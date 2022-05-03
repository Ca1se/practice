import { Manage } from './utils.js';

class Point {
    constructor(x = 0, y = 0) {
        this.data = [x, y];
    }

    get x() {
        return this.data[0];
    }

    get y() {
        return this.data[1];
    }

    /**
     * @param {number | Point} other 
     */
    add(other) {
        if(other instanceof Point) {
            return new Point(this.x + other.x, this.y + other.y);
        }

        return new Point(this.x + other, this.y + other);
    }

    /**
     * @param {number | Point} other 
     */
    sub(other) {
        if(other instanceof Point) {
            return new Point(this.x - other.x, this.y - other.y);
        }

        return new Point(this.x - other, this.y - other);
    }

    /**
     * @param {number} other 
     */
    mul(other) {
        return new Point(this.x * other, this.y * other);
    }

    /**
     * @param {number} other 
     */
    div(other) {
        return new Point(this.x / other, this.y / other);
    }
}

class Shape {
    /**
     * @param {Point} start 
     * @param {number} width 
     * @param {number} height 
     * @param {string} color 
     * @param {boolean} fill
     */
    constructor(start, width, height, color, fill) {
        this.start = start;
        this.width = width;
        this.height = height;
        this.color = color;
        this.fill = fill;

        this.id = parseInt(Math.random().toString().substring(2, 6) + Date.now().toString().substring(7));
        this.showed = false;
        this.belong = '';
    }

    show(container) {
        if(!this.showed) {
            /** @type {HTMLDivElement} */
            const wrapper = $(`<div class="canvas_wrapper" id="${'i' + this.id}"></div>`).css(
                { 
                    'width': `${this.width}px`,
                    'height': `${this.height}px`,
                    'position': 'absolute',
                    'top': this.start.y,
                    'left': this.start.x
                }
            )[0];
            /** @type {HTMLCanvasElement} */
            this.canvas = $(`<canvas width="${this.width}px" height="${this.height}px"></canvas>`)[0];
            const rotate = $(`<div class="rotate"></div>`).css(
                {
                    'width': '10px',
                    'height': '10px',
                    'position': 'absolute',
                    'top': 0,
                    'left': 0,
                    'border': '1px solid black',
                    'background-color': 'white',
                    'visibility': 'hidden'
                }
            )[0];
            const scale = $('<div class="scale"></div>').css(
                {
                    'width': '10px',
                    'height': '10px',
                    'position': 'absolute',
                    'right': 0,
                    'bottom': 0,
                    'border': '1px solid black',
                    'background-color': 'white',
                    'visibility': 'hidden'
                }
            )[0];
            wrapper.append(this.canvas);
            wrapper.append(rotate);
            wrapper.append(scale);
            $(`#${container}`).append(wrapper);
            this.belong = container;
            this.showed = true;
        }
    }

    remove() {
        if(this.showed) {
            $(`#i${this.id}`).remove();
            this.belong = '';
            this.showed = false;
        }
    }

    drawShape() { throw 'No implementation'; }
}

class Rectangle extends Shape {
    /**
     * @param {Point} origin 
     * @param {number} width 
     * @param {number} height 
     * @param {string} color
     * @param {boolean} fill
     */
    constructor(start, width, height, color, fill) {
        super(start, width, height, color, fill);
    }

    /**
     * @param {string} container
     */
    show(container) {
        super.show(container);
        Manage.shape_map.set(this.id, this);
        this.drawShape();
    }

    remove() {
        super.remove();
        Manage.shape_map.delete(this.id);
    }

    drawShape() {
        if(this.showed) {
            const ctx = this.canvas.getContext('2d');

            this.canvas.height = this.canvas.height;
            ctx.strokeStyle = this.color;
            ctx.fillStyle = this.color;

            if(this.fill) {
                ctx.fillRect(0, 0, this.width, this.height);
                return;
            }

            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(this.width, 0);
            ctx.lineTo(this.width, this.height);
            ctx.lineTo(0, this.height);
            ctx.lineTo(0, 0);
            ctx.stroke();
        }
    }
}

class Circle extends Shape {
    /**
     * @param {Point} origin 
     * @param {number} radius 
     * @param {string} color
     */
    constructor(origin, radius, color) {
        super(origin, color);
        this.radius = radius;
    }
}

class Triangle extends Shape {

}

export {
    Point,
    Shape,
    Rectangle,
    Circle,
    Triangle
}