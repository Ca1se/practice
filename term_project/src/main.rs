type FloatM44 = [[f64; 4]; 4];
type FloatM14 = [f64; 4];
type IntM44 = [[i32; 4]; 4];
fn calculate_matrix_lu(matrix_a: &FloatM44, 
    matrix_l: &mut FloatM44, matrix_u: &mut FloatM44) {
    
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

fn convert_f64_matrix(ori: &IntM44) -> FloatM44 {
    let mut a = [[0.0; 4]; 4];
    for i in 0..4 {
        for j in 0..4 {
            a[i][j] = ori[i][j] as f64;
        };
    } 
    a
}

fn calculate_matrix_x(matrix_l: &mut FloatM44, 
    matrix_u: &mut FloatM44, matrix_b: &FloatM14) -> FloatM14{
    let mut m_x = [0.0; 4];
    let mut m_y = [0.0; 4];
    for i in 0..4 {
        let mut sum = 0.0;
        for k in 0..i {
            sum = sum + matrix_l[i][k] * m_y[k];
        }
        m_y[i] = matrix_b[i] - sum;
    }
    
    for i in (0..4).rev() {
        let mut sum = 0.0;
        for k in (i + 1)..4 {
            sum = sum + matrix_u[i][k] * m_x[k];
        }
        m_x[i] = (m_y[i] - sum) / matrix_u[i][i];
    }
    m_x
}


fn main() {
    let origin_a= [[11, 20, 20, 50],
                    [50, 40, 10, 10],
                    [30, 10, 40, 20],
                    [20, 40, 40, 40]];
    let matrix_a = convert_f64_matrix(&origin_a);
    let mut matrix_u = [[0.0; 4]; 4];
    let mut matrix_l = matrix_u.clone(); 
    let matrix_b = [200.0, 250.0, 210.0, 340.0];
    calculate_matrix_lu(&matrix_a, &mut matrix_l, &mut matrix_u);
    let matrix_x = calculate_matrix_x(&mut matrix_l, &mut matrix_u, &matrix_b);
    for i in 0..4 {
        println!("x{} = {}", i + 1, matrix_x[i]);
    }
}
