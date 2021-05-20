#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy

# 前两个迭代法可用一个方程
def jacobi_gauss_seidel(c, B, f, omega = 0.00001):
    x = numpy.matrix([0, 0, 0, 0]).T
    r = None
    i = 0
    while i < 1000:
        cnt = 0
        r = B.dot(x) + f
        for i in range(0, 4):
            if abs(r[i][0] - x[i][0]) < omega:
                cnt += 1
        x = r
        if cnt == 4:
            break
        i += 1
    if i != 1000:
        if c == 0:
            print('jacobi:')
        elif c == 1:
            print('gauss_seidel:')
        else:
            print(f'SOR(omega = {omega}):')
        for i in range(0, 4):
            print(f'x{i + 1} = {float(x[i][0])}')
    else:
        print("发散")


if __name__ == "__main__":
    A = numpy.matrix([[5, 1, -1, -2], [2, 8, 1, 3], [1, -2, -4, -1], [-1, 3, 2, 7]])
    D = numpy.matrix([[5, 0, 0, 0], [0, 8, 0, 0], [0, 0, -4, 0], [0, 0, 0, 7]])
    I = numpy.matrix([[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])
    L = numpy.matrix([[0, 0, 0, 0], [2, 0, 0, 0], [1, -2, 0, 0], [-1, 3, 2, 0]]) * -1
    U = (A - D + L) * -1
    b = numpy.matrix([-2, -6, 6, 12]).T

    jacobi_B = I - D.I.dot(A)
    jacobi_f = D.I.dot(b)

    # jacobi
    jacobi_gauss_seidel(0, jacobi_B, jacobi_f)
    
    gs_B = (D - L).I.dot(U)
    gs_f = (D - L).I.dot(b)

    # gauss_seidel
    jacobi_gauss_seidel(1, gs_B, gs_f)

    omega = 1
    SOR_L = (D - omega * L).I.dot((1 - omega) * D + omega * U)
    SOR_f = omega * (D - omega * L).I.dot(b)

    jacobi_gauss_seidel(2, SOR_L, SOR_f, omega)


