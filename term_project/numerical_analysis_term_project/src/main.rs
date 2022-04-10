type FloatM44 = [[f64; 4]; 4];
type FloatM14 = [f64; 4];

fn calculate_matrix_lu(matrix_a: &FloatM44, 
    matrix_l: &mut FloatM44, matrix_u: &mut FloatM44) {
    
    //分解L, U矩阵
    for r in 0..4 {
        for i in r..4 {
            let mut sum = 0.0;
            for k in 0..r {
                sum = sum + matrix_l[r][k] * matrix_u[k][i];
            }
            matrix_u[r][i] = matrix_a[r][i] - sum;
        }

        for i in r..4 {
            let mut sum = 0.0;
            for k in 0..r {
                sum = sum + matrix_l[i][k] * matrix_u[k][r];
            }
            matrix_l[i][r] = (matrix_a[i][r] - sum) / matrix_u[r][r];
        }
    }         
}

fn calculate_matrix_x(matrix_l: &FloatM44, 
    matrix_u: &FloatM44, matrix_b: &FloatM14) -> FloatM14{
    //创建临时矩阵X, Y
    let mut m_x = [0.0; 4];
    let mut m_y = [0.0; 4];

    //计算矩阵Y
    for i in 0..4 {
        let mut sum = 0.0;
        for k in 0..i {
            sum = sum + matrix_l[i][k] * m_y[k];
        }
        m_y[i] = matrix_b[i] - sum;
    }
    //计算矩阵X
    for i in (0..4).rev() {
        let mut sum = 0.0;
        for k in (i + 1)..4 {
            sum = sum + matrix_u[i][k] * m_x[k];
        }
        m_x[i] = (m_y[i] - sum) / matrix_u[i][i];
    }
    m_x
}

fn print_matrix(matrix: &FloatM44) {
    for it in matrix {
        for i in it {
            print!("{:.2} ", i);
        }
        println!();
    }
    println!();
}


fn main() {
    //系数矩阵A
    let matrix_a= [[11.0, 20.0, 20.0, 50.0],
                    [50.0, 40.0, 10.0, 10.0],
                    [30.0, 10.0, 40.0, 20.0],
                    [20.0, 40.0, 40.0, 40.0]];
    let mut matrix_u = [[0.0; 4]; 4]; //创建矩阵U
    let mut matrix_l = matrix_u; //创建矩阵L
    let matrix_b = [200.0, 250.0, 210.0, 340.0]; //矩阵B

    //计算上三角矩阵U,下三角矩阵L
    calculate_matrix_lu(&matrix_a, &mut matrix_l, &mut matrix_u);
    print_matrix(&matrix_l);
    print_matrix(&matrix_u);
    //创建并计算矩阵X
    let matrix_x = calculate_matrix_x(&matrix_l, &matrix_u, &matrix_b);

    //打印矩阵X
    for i in 0..4 {
        println!("x{} = {}", i + 1, matrix_x[i]);
    }
}
