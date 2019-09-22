#Configuració
plotResults=false;

#Constants
Fm=48e3;
tf = 2;
n = [10, 13, 16];

v0=1;
v1=-1;

#Càlculs X1 i X2
[x1, x2, X1, X2, F] = calculateX1X2(Fm, tf, v0, v1);

if (plotResults)
    subplot(2,1,1);
    plot(F, abs(X1));
    xlabel("f(Hz)");
    title("Gràfica X1");
    subplot(2,1,2);
    plot(F, abs(X2));
    xlabel("f(Hz)");
    title("Gràfica X2");
endif

#Càlculs X3 (LFSR)

playlistX3=zeros(N+10000, columns(ns));

if(plotResults)
    figure(2);
endif
  
i = 1;
for n = ns
  [x3, X3, F1] = calculateX3(n, tf, Fm, v0, v1);
  playlistX3(1:rows(x3),i)= x3;
  if(plotResults)
    subplot(3,1,i);
    plot(F1, abs(X3));
    xlabel("f(Hz)");
    title(strcat("Gràfica X3, n = ", num2str(n)));
  endif
  i++;
endfor

#Reproducció so
play_so(x1, Fm);
pause(1);
play_so(x2, Fm);
pause(1);

for i = 1:columns(playlistX3)
  play_so(playlistX3(:, i)(playlistX3(:,i)!=0), Fm);
  pause(1);
endfor  







