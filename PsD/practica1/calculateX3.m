function [x, X, F] = calculateX3(n, tf, Fm, v0, v1)
  p=ceil(tf*Fm/(2^n - 1));
  N=(2^n - 1) * p;

  x=LFSRs(n, N, v0, v1);
  [X, F]=f_TF(x, Fm);
endfunction