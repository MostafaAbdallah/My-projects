function []=Autocorrelation( wav_track_name, frame_size_msc, frame_overlap_msc, window_typy )
result=EndPointDetection(wav_track_name, frame_size_msc, frame_overlap_msc, window_typy);
%result = Framing(wav_track_name, frame_size_msc, frame_overlap_msc, window_typy);
voic=xcorr(result (29,:));
[ r c]= size(voic);
fn=voic(:,1:ceil(c/2));
figure;
plot(fn);

end