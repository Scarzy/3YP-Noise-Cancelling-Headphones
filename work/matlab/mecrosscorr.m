function [ out ] = mecrosscorr( ina , inb , del )
%MECROSSCORR Achieves crosscorrelation
%   Achieves cross-correlation in a form that can be implemented in C for
%   implementation on hardware.
%       in1:    f[n]
%       in2:    g[n]
%       len:    Max delay


%MATLAB error checking, can't be implemented in C
if (length(ina) ~= length(inb))
    return;
end

%inf = 300;
%
%Start by assuming it's only real values
%for n = -len:len
%    sum = 0;
%    for i = -inf:inf
%        if(i <= 0 || i > len)
%            a1 = 0;
%        else
%            a1 = ina(i);
%        end
%        if((n+i) <= 0 || (n+i) > len)
%            a2 = 0;
%        else
%            a2 = inb(n+i);
%        end
%        sum = sum + (a1 * a2);
%    end
%    out(n+len+1) = sum;
%end

%Mathematical fiddling
%Cross-Correlation = f[n] convolved with g[-n]
%                  = ifft( F[n] * G[-n] )

%Reverse vector b
%aplain = ina;
%for i = 1:length(inb)
%    bplain(i,1) = inb(length(inb)-(i-1));
%end;
%
%size(aplain)
%size(bplain)
%
%FFT
%afft = fft(aplain);
%bfft = fft(bplain);
%
%size(afft)
%size(bfft)
%
%Multiply
%mfft = afft * bfft;
%
%iFFT
%out = ifft(mfft);

%
N = length(ina);

%Calculate means
amean = 0;
for i = 1:N
    amean = amean + ina(i);
end
amean = amean / N;

bmean = 0;
for i = 1:N
    bmean = bmean + inb(i);
end
bmean = bmean / N;

%All Delays
for d = -del:del
    %E[(ina(i) - amean) * (inb(i-d) - bmean)]
    num = 0;
    for i = 1:N
        j = i + d;
        if( (j < 1) | (j > N) )
            %num = num + ((ina(i) - amean) * (-bmean));
        else
            num = num + ((ina(i) - amean) * (inb(j) - bmean));
        end
    end
    
    %sqrt(E[ina(i) - amean]^2*E[inb(i-d) - bmean]^2)
    suma = 0;
    sumb = 0;
    for i = 1:N
        suma = suma + ((ina(i) - amean) * (ina(i) - amean));
        sumb = sumb + ((inb(i) - bmean) * (inb(i) - bmean));
    end
    s = sqrt(suma * sumb);
    
    out(d + del + 1) = num / s;
end

end

