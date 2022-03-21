import taichi as ti

window_width  = 512
window_height = 512

ti.init(arch = ti.gpu)
canvas = ti.field(dtype = ti.f32, shape = (window_width, window_height))

@ti.kernel
def draw_line(c: ti.template()):
    for i, j in c:
        c[i, j] = ti.random()

gui = ti.GUI('test', res = (window_width, window_height))

if __name__ == '__main__':
    pass