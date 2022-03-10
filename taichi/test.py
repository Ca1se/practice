from tkinter import N
import taichi as ti
ti.init(arch = ti.gpu)

'''
@ti.kernel
def foo():
    res = ti.field(dtype = ti.i64, shape = ())
    for i in range(10000000):
'''

if __name__ == "__main__":
    a = ti.field(dtype = ti.i64, shape = ())
    a[None] = a[None] + 1
    # a[None] = a[None] + 1
    print(a[None])
