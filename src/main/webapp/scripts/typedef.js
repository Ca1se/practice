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

    set x(x) {
        this.data[0] = x;
    }

    set y(y) {
        this.data[1] = y;
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
    /** @type {Map<number, Shape>} */
    static s_shapes = new Map;

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
        this.rotate_deg = 0;
        this.showed = false;
    }

    show(container) {
        if(!this.showed) {
            /** @type {HTMLDivElement} */
            this.wrapper = $(`<div class="canvas_wrapper" id="${'i' + this.id}"></div>`).css(
                { 
                    'width': `${this.width}px`,
                    'height': `${this.height}px`,
                    'position': 'absolute',
                    'top': this.start.y,
                    'left': this.start.x,
                    'z-index': 0
                }
            )[0];
            /** @type {HTMLCanvasElement} */
            this.canvas = $(`<canvas width="${this.width}px" height="${this.height}px"></canvas>`).css({ 'position': 'absolute' })[0];
            this.frame = $(`<div class="control_frame"></div>`)[0];
            /** @type {HTMLDivElement} */
            this.rotate = $(`<div class="rotate control_bar"></div>`)[0];
            /** @type {HTMLDivElement} */
            this.scale = $('<div class="scale control_bar"></div>')[0];
            this.frame.append(this.rotate);
            this.frame.append(this.scale);
            this.wrapper.append(this.canvas);
            this.wrapper.append(this.frame);
            $(`#${container}`).append(this.wrapper);
            this.showed = true;
            Shape.s_shapes.set(this.id, this);
        }
    }

    remove() {
        if(this.showed) {
            $(`#i${this.id}`).remove();
            this.showed = false;
            Shape.s_shapes.delete(this.id);
            console.log(Shape.s_shapes.size);
        }
    }

    drawShape() { throw 'No implementation'; }

    /**
     * @param {boolean} show 
     */
    setZoomFrame(show) {
        if(show) {
            $(this.frame).css('visibility', 'visible');
        }else {
            $(this.frame).css('visibility', 'hidden');
        }
    }

    /** @typedef {{ start_offset?: Point, scale_offset?: Point, z_index?: number, rotate?: number, color?: string, fill?: boolean }} Attrib */

    /**
     * @param {Attrib} attrib 
     */
    update(attrib) {
        if(attrib.start_offset) {
            this.start = this.start.add(attrib.start_offset);
            this.wrapper.style.left = this.start.x + 'px';
            this.wrapper.style.top = this.start.y + 'px';
        }else if(attrib.scale_offset) {
            this.width = Math.max(30, this.width + attrib.scale_offset.x);
            this.height = Math.max(30, this.height + attrib.scale_offset.y);
            this.wrapper.style.width = this.width + 'px';
            this.wrapper.style.height = this.height + 'px';
            this.canvas.width = this.width;
            this.canvas.height = this.height;
            this.drawShape();
        }else if(attrib.z_index) {
            this.wrapper.style.zIndex = Math.max(0, Math.min(20, attrib.z_index));
        }else if(attrib.rotate) {
            this.rotate_deg = (this.rotate_deg + attrib.rotate + 360) % 360;
            this.wrapper.style.transform = `rotate(${this.rotate_deg}deg)`;
        }else if(attrib.color) {
            this.color = attrib.color;
            this.drawShape();
        }else if(attrib.fill != undefined) {
            this.fill = attrib.fill;
            this.drawShape();
        }
    }
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
        this.drawShape();
    }

    drawShape() {
        if(this.showed) {
            const ctx = this.canvas.getContext('2d');

            this.canvas.width = this.canvas.width;
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
            ctx.closePath();
            ctx.stroke();
        }
    }
}

class Circle extends Shape {
    constructor(start, width, height, color, fill) {
        super(start, width, height, color, fill);
    }

    show(container) {
        super.show(container);
        this.drawShape();
    }

    drawShape() {
        if(this.showed) {
            const ctx = this.canvas.getContext('2d');

            this.canvas.width = this.canvas.width;
            ctx.strokeStyle = this.color;
            ctx.fillStyle = this.color;

            ctx.save();
            let r = (this.width > this.height) ? this.width : this.height;
            let ratiox = this.width / r;
            let ratioy = this.height / r;
            ctx.scale(ratiox, ratioy);
            ctx.beginPath();
            ctx.arc(this.width / 2 / ratiox, this.height / 2 / ratioy, r / 2 - 1, 0, 2 * Math.PI, false);
            ctx.closePath();
            ctx.restore();

            if(this.fill) {
                ctx.fill();
                return;
            }
            ctx.stroke();
        }
    }
}

class Triangle extends Shape {
    constructor(start, width, height, color, fill) {
        super(start, width, height, color, fill);
    }

    show(container) {
        super.show(container);
        this.drawShape();
    }

    drawShape() {
        if(this.showed) {
            const ctx = this.canvas.getContext('2d');

            this.canvas.width = this.canvas.width;
            ctx.strokeStyle = this.color;
            ctx.fillStyle = this.color;

            ctx.beginPath();
            ctx.moveTo(this.width / 2, 0);
            ctx.lineTo(this.width, this.height);
            ctx.lineTo(0, this.height);
            ctx.lineTo(this.width / 2, 0);
            ctx.closePath();
            
            if(this.fill) {
                ctx.fill();
                return;
            }
            ctx.stroke();
        }
    }
}

class Hexagon extends Shape {
    constructor(start, width, height, color, fill) {
        super(start, width, height, color, fill);
    }

    show(container) {
        super.show(container);
        this.drawShape();
    }

    drawShape() {
        if(this.showed) {
            const ctx = this.canvas.getContext('2d');

            this.canvas.width = this.canvas.width;
            ctx.strokeStyle = this.color;
            ctx.fillStyle = this.color;

            ctx.beginPath();
            ctx.moveTo(this.width / 4, 0);
            ctx.lineTo(this.width / 4 * 3, 0);
            ctx.lineTo(this.width, this.height / 2);
            ctx.lineTo(this.width / 4 * 3, this.height);
            ctx.lineTo(this.width / 4, this.height);
            ctx.lineTo(0, this.height / 2);
            ctx.lineTo(this.width / 4, 0);
            ctx.closePath();

            if(this.fill) {
                ctx.fill();
                return;
            }

            ctx.stroke();
        }
    }
}

export {
    Point,
    Shape,
    Rectangle,
    Circle,
    Triangle,
    Hexagon
}