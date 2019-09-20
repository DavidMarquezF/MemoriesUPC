calcX1X2=true;
plotX1X2=true;
calcX3=true;
plotX3=true;

Fm=48e3;
tf = 2;
N = Fm*tf;

if (calcX1X2) 
  # Càlcul X1
  x1=randn(N, 1);

  [X1, F1] = f_TF(x1, Fm);

  # Càlcul X2
  x2=x1;
  x2(x2>=0)=1;
  x2(x2<0)=-1;

  [X2, ~] = f_TF(x2, Fm);
  if (plotX1X2)
    subplot(2,1,1);
    plot(F1, abs(X1));
    xlabel("f(Hz)");
    title("Gràfica X1");
    subplot(2,1,2);
    plot(F1, abs(X2));
    xlabel("f(Hz)");
    title("Gràfica X2");
  endif
endif

#Càlcul X3
playlistX3=[];
if (calcX3)
  if(plotX3)
    figure(2);
  endif
  
  i = 1;
  for n = [10, 13, 16]
    p=ceil(tf*Fm/(2^n - 1));
    N=(2^n - 1) * p;

    x3=LFSRs(n, N);
    [X3, F]=f_TF(x3, Fm);
    
    if(plotX3)
      subplot(3,1,i)
      plot(F, abs(X3));
      xlabel("f(Hz)");
      title(strcat("Gràfica X3, n = ", num2str(n)));
    endif
    playlist = [playlist, x3];
    i++;
  endfor
endif

if(calcX1X2)
play_so(x1, Fm);
pause(1);
play_so(x2, Fm);
pause(1);
endif
for i = 1:columns(playlistX3)
  play_so(playlistX3(:, i), Fm);
  pause(1);
endfor  
