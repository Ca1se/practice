import matplotlib.pyplot as plt
import numpy


def create_interval_points(n, func_fx, func_dist):
    xs = []
    ys = []
    for k in range(0, n + 1):
        x = func_dist(k, n)
        y = func_fx(x)
        xs.append(x)
        ys.append(y)
    return xs, ys


def calculate_difference(n, ys):
    diffs = []
    for i in range(0, n + 1):
        t = 0
        for j in range(0, i + 1):
            t += ((-1) ** j) * cnk(i, j) * ys[i - j]
        diffs.append(t)
    return diffs


def cnk(n, k):
    return ank(n, k) / ank(k, k)


def ank(n, k):
    if n == 0:  return 1
    res = 1
    for i in range(0, k):
        res *= n
        n -= 1
    return res


def interval_newton(n, diffs, x, x0, h):
    t = (x - x0) / h
    res = diffs[0]
    tmp = t
    for i in range(1, n + 1):
        res += tmp / ank(i, i) * diffs[i]
        tmp *= t - 1
        t -= 1
    return res


def print_interval_newton_lx(n, diffs):
    newton = f"L{n}x = {diffs[0]}"
    now_t = "t"
    for i in range(1, n + 1):
        newton += f" + ({diffs[i] / ank(i, i)}) * " + now_t
        now_t += f"(t-{i})"
    print(newton)


# 题中给定的fx
def pre_func_fx(x):
    return 1 / (1 + x * x)


# 题中给定的距离函数
def pre_func_dist(k, n):
    return -5 + 10 / n * k


if 1 == 1:
    n_set = [2, 4, 6, 8, 10]

    # 绘制图像所需的x集合
    xs = [i for i in numpy.arange(-10.0, 10.001, 0.001)]
    fx_ys = []
    for x in xs:
        fx_ys.append(pre_func_fx(x))
    plt.plot(xs, fx_ys, label="f(x)")

    for i in n_set:
        x_set, y_set = create_interval_points(i, pre_func_fx, pre_func_dist)
        # fx0 的n阶差分
        differences = calculate_difference(i, y_set)
        newton_ys = []
        print_interval_newton_lx(i, differences)
        
        for x in xs:
            newton_ys.append(interval_newton(i, differences, x, -5, 10 / i))
        plt.plot(xs, newton_ys, label=f'L{i}x')
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.ylim(ymin=-2, ymax=2)
    plt.show()
