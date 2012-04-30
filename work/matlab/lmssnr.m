leng = 50; %The max filter length

lmssnrarr = zeros(leng,1);

ins = as; %fileload('spacerabbits_noise.wav');
inn = as; %fileload('NYG.wav');
ins = ins(1:min(length(ins),length(inn)));
inn = inn(1:min(length(ins),length(inn)));

%for i = leng
    hlms2 = dsp.LMSFilter('Length', i, ...
        'Method', 'Normalized LMS',...
       'AdaptInputPort', true, ...
       'StepSizeSource', 'Input port', ...
       'WeightsOutputPort', false);
    x = inn; % Noise
    d = ins; %ins + circshift(0.8*inn,5); % Noise + Signal
    a = 0.8; % adaptation control
    mu = 0.0005; % step size
    [y, err] = step(hlms2, x, d, mu, a);
    
%    [psnr, mse, maxerr, l2rat] = measerr(err,ins);
%    lmssnrarr(i) = psnr;
%end

plot(err);
%title{'Error feedback from the LMS cancellation of two sine waves');
xlabel('Sample');
ylabel('Error value');