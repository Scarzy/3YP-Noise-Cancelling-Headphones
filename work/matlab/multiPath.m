function [ out ] = multiPath( sig , chain , delay )
%multiPath Applies a multi path effect to a signal
%   Takes in a signal and passes it through a Tapped Delay Line. This
%   mimics the multipath nature of signals through a transmission medium.
%                                                                        
%   sig:    The signal to have the function applied to it
%   chain:  The gains of the taps on the line
%   delay:  The delay length in number of items in the array between each
%           tap

sig = [1 0.3 0.8 0.1 0.6 0 0.2];
chain = [0.9 0.4 0.8 0.1 0.4];
delay = 1;

for i = 1:length(sig)
    
end

out = [zeros([1 length(sig)]) zeros([1 ((length(chain)-1)*delay)])];
for i = 1:length(chain)
    out = out + [zeros([1 (i-1)]) sig*chain(i) zeros([1 (length(out)-length(sig)-(i-1))])];;
end
%out = out + [zeros()][sig]];

end

