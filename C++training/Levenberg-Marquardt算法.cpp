#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// ģ�ͺ�����y = a * exp(b * x) + c
double model(double x, const VectorXd& p) {
    return p(0) * exp(p(1) * x) + p(2);
}

// ����в� r_i = y_i - model(x_i)
VectorXd calculateResiduals(int m, const double* x, const double* y, const VectorXd& p) {
    VectorXd residuals(m);
    for (int i = 0; i < m; ++i) {
        residuals(i) = y[i] - model(x[i], p);
    }
    return residuals;
}

// �����ſɱȾ��� J_{i,j} = df_i / dp_j
MatrixXd calculateJacobian(int m, const double* x, const VectorXd& p) {
    MatrixXd J(m, p.size());
    for (int i = 0; i < m; ++i) {
        double xi = x[i];
        double exp_term = exp(p(1) * xi);
        J(i, 0) = exp_term;                  // df/dp0
        J(i, 1) = p(0) * xi * exp_term;      // df/dp1
        J(i, 2) = 1.0;                       // df/dp2 ��ע��ԭ�����������ӦΪ����
    }
    return J;
}

// Levenberg-Marquardt �㷨ʵ��
VectorXd levenbergMarquardt(
    int m, const double* x, const double* y,
    VectorXd p_init,
    double lambda_init = 0.01,
    int max_iter = 100,
    double tol = 1e-6) {

    VectorXd p = p_init;
    double lambda = lambda_init;

    // ��ʼ����
    for (int iter = 0; iter < max_iter; ++iter) {
        VectorXd residuals = calculateResiduals(m, x, y, p);   // �в�
        MatrixXd J = calculateJacobian(m, x, p);               // �ſɱȾ���

        // �������淽�̣�(J^T * J + lambda * I) * delta_p = J^T * residuals
        MatrixXd JTJ = J.transpose() * J;
        MatrixXd lambdaI = lambda * MatrixXd::Identity(p.size(), p.size());
        MatrixXd A = JTJ + lambdaI;
        VectorXd b = J.transpose() * residuals;

        VectorXd delta_p = A.ldlt().solve(b);

        // ���²���
        VectorXd p_new = p - delta_p;

        // �ж�����
        if ((p_new - p).norm() < tol) {
            cout << "��������������: " << iter << endl;
            break;
        }

        // �ж��Ƿ�������
        double cost_old = residuals.squaredNorm();
        residuals = calculateResiduals(m, x, y, p_new);
        double cost_new = residuals.squaredNorm();

        if (cost_new < cost_old) {
            p = p_new;
            lambda /= 10;  // ��С��������
        } else {
            lambda *= 10;  // ������������
        }
    }

    return p;
}

int main() {
    // ���ݵ㣨��������ʵ�����ݣ�
    const int m = 6;
    double x[m] = {0, 1, 2, 3, 4, 5};
    double y[m] = {2.5, 3.1, 4.8, 7.3, 11.0, 15.0};

    // ��ʼ�²���� (a, b, c)
    VectorXd p_init(3);
    p_init << 1.0, 0.5, 1.0;

    // ʹ�� Levenberg-Marquardt �㷨�������
    VectorXd p_opt = levenbergMarquardt(m, x, y, p_init);

    // ������
    cout << "�Ż���Ĳ���: a = " << p_opt(0) << ", b = " << p_opt(1) << ", c = " << p_opt(2) << endl;

    // ������ֵ
    for (int i = 0; i < m; ++i) {
        cout << "x = " << x[i]
             << ", y = " << y[i]
             << ", ���ֵ = " << model(x[i], p_opt) << endl;
    }

    return 0;
}
