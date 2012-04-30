leng = 1000; %The max filter length

lmssnrarr = zeros(leng,1);

ins = fileload('spacerabbits_noise.wav');
inn = fileload('NYG.wav');
ins = ins(1:min(length(ins),length(inn)));
inn = inn(1:min(length(ins),length(inn)));

for i = 930:leng
    hlms2 = dsp.LMSFilter('Length', i, ...
        'Method', 'Normalized LMS',...
       'AdaptInputPort', true, ...
       'StepSizeSource', 'Input port', ...
       'WeightsOutputPort', false);
    x = inn; % Noise
    d = ins + circshift(0.8*inn,5); % Noise + Signal
    a = 0.8; % adaptation control
    mu = 0.0005; % step size
    [y, err] = step(hlms2, x, d, mu, a);
    
    [psnr, mse, maxerr, l2rat] = measerr(err,ins);
    lmssnrarr(i) = psnr;
    save(strcat('lmssnr1000_vars/1000_',int2str(i),'.mat'),'lmssnrarr')
end

plot(1:leng,lmssnrarr);
xlabel('Filter Length')
ylabel('SNR in dB')
