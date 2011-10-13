function [ out ] = cancel( mix , nui )
%CANCEL removes nui (if present) from inside mix
%   Detects if mix contains nui, and if so, it removes it
%   Currently I do not believe it can cope with varying intensities, or
%   even if it copes with no nui present

%check to see if contained, and what shift is applied
%is exhaustive
cc = crosscorr(mix, nui, (length(mix)-1));

%detect what shift is applied
[mag, shift] = dPeak(cc);
shift = ceil(length(cc)/2) - shift;

%apply shift
inu = circshift(nui,shift);

%remove from signal
out = mix - inu;

end

