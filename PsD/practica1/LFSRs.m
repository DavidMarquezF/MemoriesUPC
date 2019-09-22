function x = LFSRs(n=10,N= 1e5, v0=1, v1=-1)
  x=zeros(N,1);
  sr=ones(n,1);
  for i = 1:N
    switch(n)
      case 10
        in= xor(sr(10),sr(7));
      case 11
        in = xor(sr(11), sr(9));
      case 12
        in = xor(xor(sr(12), sr(11)), xor(sr(10), sr(4)));
      case 13
        in = xor(xor(sr(13), sr(12)), xor(sr(11), sr(8)));
      case 14
        in = xor(xor(sr(14), sr(13)), xor(sr(12), sr(2)));
      case 15
        in = xor(sr(15), sr(14));
      case 16
        in= xor(xor(sr(15),sr(16)), xor(sr(13), sr(4)));
    endswitch
    sr(2:n) = sr(1:n-1);
    sr(1)=in;
    x(i)=in;
  end
  x(x==1)=v0;
  x(x==0)=v1;
  
  LFSRs = x;
endfunction