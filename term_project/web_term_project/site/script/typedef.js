// ts-check

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
}

class RGBA {
    constructor(r = 0, g = 0, b = 0, a = 1) {
        this.data = [r, g, b, a];
    }

    get r() {
        return this.data[0];
    }

    get g() {
        return this.data[1];
    }

    get b() {
        return this.data[2];
    }

    get a() {
        return this.data[3];
    }
}


export {
    Point,
    RGBA
}