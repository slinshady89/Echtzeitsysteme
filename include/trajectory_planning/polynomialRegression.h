#ifndef _POLYNOMIALREGRESSION_H
#define _POLYNOMIALREGRESSION_H
/**
 * PURPOSE:
 *
 *  Polynomial Regression aims to fit a non-linear relationship to a set of
 *  points. It approximates this by solving a series of linear equations using
 *  a least-squares approach.
 *
 *  We can model the expected value y as an nth degree polynomial, yielding
 *  the general polynomial regression model:
 *
 *  y = a0 + a1 * x + a2 * x^2 + ... + an * x^n
 * @author Chris Engelsma
 */
#include<vector>
#include<stdlib.h>

template <class TYPE>
class PolynomialRegression {
  public:

    PolynomialRegression();
    virtual ~PolynomialRegression();

    bool fitIt(
      const std::vector<TYPE> & x,
      const std::vector<TYPE> & y,
      const int &             order,
      std::vector<TYPE> &     coeffs);

    double calcCurv(
      const std::vector<TYPE> &polyCoeffs,
      double at
      );
};

template <class TYPE>
PolynomialRegression<TYPE>::PolynomialRegression() {};


template <class TYPE>
double PolynomialRegression<TYPE>::calcCurv(
  const std::vector<TYPE> &polyCoeffs,
  double at)
{
  auto poly_y = 0.0;
  auto poly_dy = 0.0;
  auto poly_ddy = 0.0;

  for (size_t i = 0; i < polyCoeffs.size(); i++){
    poly_y += polyCoeffs[i]* std::pow(at,i);
  }
  for (size_t i = 1; i < polyCoeffs.size(); i++){
    poly_dy += polyCoeffs[i]* std::pow(at,i-1)*i;
  }
  for (size_t i = 2; i < polyCoeffs.size(); i++){
    poly_ddy += polyCoeffs[i]* std::pow(at,i-2)*(i-1);
  }

  auto poly_denom = (1+poly_dy)*(1+poly_dy);
  poly_denom = std::sqrt(std::pow(poly_denom,3));
  return poly_ddy / poly_denom;
}


template <class TYPE>
bool PolynomialRegression<TYPE>::fitIt(
  const std::vector<TYPE> & x,
  const std::vector<TYPE> & y,
  const int &               order,
  std::vector<TYPE> &       coeffs)
{
  // The size of xValues and yValues should be same
  if (x.size() != y.size()) {
    std::__throw_runtime_error( "The size of x & y arrays are different" );
    return false;
  }
  // The size of xValues and yValues cannot be 0, should not happen
  if (x.size() == 0 || y.size() == 0) {
    std::__throw_runtime_error( "The size of x or y arrays is 0" );
    return false;
  }

  size_t N = x.size();
  int n = order;
  int np1 = n + 1;
  int np2 = n + 2;
  int tnp1 = 2 * n + 1;
  TYPE tmp;

  // X = vector that stores values of sigma(xi^2n)
  std::vector<TYPE> X(tnp1);
  for (int i = 0; i < tnp1; ++i) {
    X[i] = 0;
    for (int j = 0; j < N; ++j)
      X[i] += (TYPE)pow(x.at(j), i);
  }

  // a = vector to store final coefficients.
  std::vector<TYPE> a(np1);

  // B = normal augmented matrix that stores the equations.
  std::vector<std::vector<TYPE> > B(np1, std::vector<TYPE> (np2, 0));

  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= n; ++j)
      B[i][j] = X[i + j];

  // Y = vector to store values of sigma(xi^n * yi)
  std::vector<TYPE> Y(np1);
  for (int i = 0; i < np1; ++i) {
    Y[i] = (TYPE)0;
    for (int j = 0; j < N; ++j) {
      Y[i] += (TYPE)pow(x[j], i)*y[j];
    }
  }

  // Load values of Y as last column of B
  for (int i = 0; i <= n; ++i)
    B[i][np1] = Y[i];

  n += 1;
  int nm1 = n-1;

  // Pivotisation of the B matrix.
  for (int i = 0; i < n; ++i)
    for (int k = i+1; k < n; ++k)
      if (B[i][i] < B[k][i])
        for (int j = 0; j <= n; ++j) {
          tmp = B[i][j];
          B[i][j] = B[k][j];
          B[k][j] = tmp;
        }

  // Performs the Gaussian elimination.
  // (1) Make all elements below the pivot equals to zero
  //     or eliminate the variable.
  for (int i=0; i<nm1; ++i)
    for (int k =i+1; k<n; ++k) {
      TYPE t = B[k][i] / B[i][i];
      for (int j=0; j<=n; ++j)
        B[k][j] -= t*B[i][j];         // (1)
    }

  // Back substitution.
  // (1) Set the variable as the rhs of last equation
  // (2) Subtract all lhs values except the target coefficient.
  // (3) Divide rhs by coefficient of variable being calculated.
  for (int i=nm1; i >= 0; --i) {
    a[i] = B[i][n];                   // (1)
    for (int j = 0; j<n; ++j)
      if (j != i)
        a[i] -= B[i][j] * a[j];       // (2)
    a[i] /= B[i][i];                  // (3)
  }

  coeffs.resize(a.size());
  for (size_t i = 0; i < a.size(); ++i)
    coeffs[i] = a[i];

  return true;
}

template<class TYPE>
PolynomialRegression<TYPE>::~PolynomialRegression() {

}

#endif //_POLYNOMIALREGRESSION_H
