// ts-check

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
     * @param {Point} origin 
     * @param {string} color
     */
    constructor(origin, color) {
        this.origin = origin,
        this.color = color;

        // this.up = new Point(Math.sqrt(2) / 2, Math.sqrt(2) / 2);
        this.up = new Point(0, -1);
        this.id = parseInt(Math.random().toString().substring(2, 6) + Date.now().toString().substring(7));
        this.showed = false;
        this.belong = '';
    }

    /**
     * @param {string} container
     * @param {Point} xy
     * @param {number} width
     * @param {number} height
     */
    show(container, xy, width, height) {
        const item = $(`<canvas id="${'i' + this.id}" width="${width}" height="${height}"></canvas>`).css(
            { 
                'position': 'absolute',
                'top': xy.y,
                'left': xy.x
            }
        );
        $(`#${container}`).append(item);
        this.belong = container;
        this.showed = true;

        /** @type {HTMLCanvasElement} */
        const html = item[0];
        this.ctx = html.getContext('2d');
    }

    remove() {
        $(`#${this.id}`).remove();
        this.belong = '';
        this.showed = false;
    }

    /**
     * @param {Point} min_xy
     * @param {boolean} fill
     */
    drawShape(min_xy, fill) { throw 'No implementation'; }

    /**
     * @param {boolean} enable 
     */
    setZoomFrame(enable) { throw 'No implementation'; }


}

class Rectangle extends Shape {
    /**
     * @param {Point} origin 
     * @param {number} width 
     * @param {number} height 
     * @param {string} color
     */
    constructor(origin, width, height, color) {
        super(origin, color);
        this.width = width;
        this.height = height;
    }

    /**
     * @param {Point} origin
     * @returns {Point[]}
     */
    getVertice(origin) {
        const v_offset = this.up.mul(this.height / 2);
        const h_offset = (new Point(this.up.y, -this.up.x)).mul(this.width / 2);

        return [
            origin.add(v_offset).add(h_offset),
            origin.add(v_offset).sub(h_offset),
            origin.sub(v_offset).sub(h_offset),
            origin.sub(v_offset).add(h_offset)
        ];
    }

    /**
     * @param {string} container
     */
    show(container) {
        const points = this.getVertice(this.origin);
        const min_xy = new Point(Math.min(points[0].x, points[1].x, points[2].x, points[3].x) - 10,
                                 Math.min(points[0].y, points[1].y, points[2].y, points[3].y) - 10);
        const max_xy = new Point(Math.max(points[0].x, points[1].x, points[2].x, points[3].x) + 10,
                                 Math.max(points[0].y, points[1].y, points[2].y, points[3].y) + 10);
        Manage.shape_map.set(this.id, this);
        super.show(container, min_xy, max_xy.x - min_xy.x, max_xy.y - min_xy.y);
        this.drawShape(min_xy, false);
    }

    remove() {
        Manage.shape_map.delete(this.id);
        super.remove();
    }

    /**
     * @param {Point} min_xy
     * @param {boolean} fill
     */
    drawShape(min_xy, fill) {
        const ori = this.origin.sub(min_xy);
        const points = this.getVertice(ori);
        const ctx = this.ctx;
        ctx.lineWidth = 5;
        ctx.beginPath();
        ctx.moveTo(points[3].x, points[3].y);
        for(let i = 0; i < points.length; i++) {
            ctx.lineTo(points[i].x, points[i].y);
        }
        ctx.closePath();
        if(fill) {
            ctx.fillStyle = this.color;
            ctx.fill();
        }else {
            ctx.strokeStyle = this.color;
            ctx.stroke();
        }
    }

    /**
     * @param {boolean} enable 
     */
    setZoomFrame(enable) { throw 'No implementation'; }

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