ins = fileload('spacerabbits_noise.wav');
inn = fileload('NYG.wav');
ins = ins(1:min(length(ins),length(inn)));
inn = inn(1:min(length(ins),length(inn)));

hlms2 = dsp.LMSFilter('Length', 11, ...
   'Method', 'Normalized LMS',...
   'AdaptInputPort', true, ...
   'StepSizeSource', 'Input port', ...
   'WeightsOutputPort', false);
hfilt2 = dsp.DigitalFilter(...
   'TransferFunction', 'FIR (all zeros)', ...
   'Numerator', fir1(10, [.5, .75]));
x = inn; %rand(99901,1) + transpose(cos(10*(0:.0005:49.95))); % Noise
d = ins + 0.8*inn; %x + sin(0:.0005:49.95)'; % Noise + Signal
a = 0.8; % adaptation control
mu = 0.0005; % step size
[y, err] = step(hlms2, x, d, mu, a);

subplot(2,1,1), plot(d), title('Noise + Signal'), axis([0 14*10^6 -8*10^4 8*10^4]);
subplot(2,1,2),plot(err), title('Signal'), axis([0 14*10^6 -8*10^4 8*10^4]);

filewrite('lms_noisy_80.wav',d)
filewrite('lms_from_matlabs_code_80',err)