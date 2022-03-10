import taichi as ti
import time

ti.init(arch = ti.gpu, default_ip=ti.i64)

@ti.kernel
def foo(inp: ti.i64) -> ti.i64:
    res = 0
    for o in range(inp):
        for q in range(inp):
            for x in range(inp):
                for e in range(inp):
                    for r in range(inp):
                        for k in range(inp):
                            for j in range(inp):
                                for i in range(inp):
                                    res += 1
    return res

'''
def foo_cpu() -> ti.i32:
    res = ti.field(ti.i64, 0)
    for i in range(1000000000):
        res += 1
    return res
'''

if __name__ == "__main__":
    '''
    start = time.time()
    print(f'cpu: {foo_cpu()}')
    end = time.time()
    print(f'time: {end - start}')
    '''
    start = time.time()
    print(f'gpu: {foo(2000000000)}')
    end = time.time()
    print(f'time: {end - start}')