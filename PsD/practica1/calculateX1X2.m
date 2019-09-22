function [x1, x2, X1, X2, F1] = calculateX1X2(Fm, tf, v0=1, v1=-1)
  N = Fm*tf;
  x1=randn(N, 1);

  [X1, F1] = f_TF(x1, Fm);
  x2=x1;
  x2(x2>=0)=v0;
  x2(x2<0)=v1;

  [X2, ~] = f_TF(x2, Fm);
endfunction  