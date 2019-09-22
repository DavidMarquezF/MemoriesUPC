#Configuració
plotResults=true;

#Constants
Fm3=48e3;
nr=3;
Fm4=Fm3*nr;
tf = 2;

v0=-1;
v1=1;



if(plotResults)
   figure();
endif
  
i = 1;
for n = [13]
  p=ceil(tf*Fm3/(2^n - 1));
  N=(2^n - 1) * p;
  x3=LFSRs(n, N);
  [X3, F]=f_TF(x3, Fm3);
    
  if(plotResults)
    subplot(3,1,i)
    plot(F, abs(X3));
    xlabel("f(Hz)");
    title(strcat("Gràfica X3, n = ", num2str(n)));
  endif
  i++;
endfor

x4 = repmat(x3, 1, nr)';
x4=x4(:)';  
  
play_so(x3, Fm3);
pause(1);
play_so(x4, Fm4);
