#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

// ��������������������
const int MAX_SAMPLES = 1000;
const int MAX_CATEGORIES = 20;

// ٤�����Ķ���
double logGamma(double x) {
    return lgamma(x); // C++ ��׼���е� lgamma ����
}

// ����������׷ֲ��Ķ�����Ȼ
double logLikelihood(int N, int K, const double samples[][MAX_CATEGORIES], const double alpha[]) {
    double logL = 0.0;

    for (int i = 0; i < N; ++i) {
        const double* x = samples[i];

        // ���϶�����Ȼ����
        for (int j = 0; j < K; ++j) {
            logL += (alpha[j] - 1) * log(x[j]);
        }
    }

    // �����һ����
    double sumAlpha = 0.0;
    for (int j = 0; j < K; ++j) {
        sumAlpha += alpha[j];
    }

    double logBeta = 0.0;
    for (int j = 0; j < K; ++j) {
        logBeta += logGamma(alpha[j]);
    }

    logL -= logGamma(sumAlpha);
    logL -= logBeta;

    return logL;
}

// ʹ���ݶ��½������Ƶ������׷ֲ��ĳ�����
void estimateDirichletParams(int N, int K, const double samples[][MAX_CATEGORIES], double alpha[], int maxIter = 1000, double tol = 1e-6) {
    // ��ʼ�� alpha ����
    for (int j = 0; j < K; ++j) {
        alpha[j] = 1.0;
    }

    // �ݶ��½���
    for (int iter = 0; iter < maxIter; ++iter) {
        double grad[MAX_CATEGORIES] = {0};

        // �����ݶ�
        for (int i = 0; i < N; ++i) {
            const double* x = samples[i];
            for (int j = 0; j < K; ++j) {
                grad[j] += log(x[j]);
            }
        }

        // ���� alpha ����
        double stepSize = 0.1;
        bool converged = true;
        for (int j = 0; j < K; ++j) {
            double newAlpha = alpha[j] + stepSize * grad[j];
            if (newAlpha <= 0) newAlpha = 1e-6;
            if (fabs(newAlpha - alpha[j]) > tol) {
                converged = false;
            }
            alpha[j] = newAlpha;
        }

        if (converged) break;
    }
}

int main() {
    int N, K;

    cout << "Enter the number of samples (N): ";
    cin >> N;
    assert(N <= MAX_SAMPLES);

    cout << "Enter the number of categories (K): ";
    cin >> K;
    assert(K <= MAX_CATEGORIES);

    double samples[MAX_SAMPLES][MAX_CATEGORIES];

    cout << "Enter the samples (each sample is a vector of K probabilities):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            cin >> samples[i][j];
        }
    }

    double alpha[MAX_CATEGORIES]; // �洢���Ƴ��� alpha ����

    // ʹ�������Ȼ���ƹ��Ƶ������׷ֲ��Ĳ���
    estimateDirichletParams(N, K, samples, alpha);

    cout << "Estimated alpha parameters of the Dirichlet distribution:\n";
    for (int j = 0; j < K; ++j) {
        cout << alpha[j] << " ";
    }
    cout << endl;

    // ��ѡ�����������Ȼֵ
    double ll = logLikelihood(N, K, samples, alpha);
    cout << "Log-likelihood: " << ll << endl;

    return 0;
}
