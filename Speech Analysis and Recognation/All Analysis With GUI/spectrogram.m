function [InversFM] = spectrogram( wav_track_name, frame_size_msc, frame_overlap_msc, window_typy )

[ Frame_matrix ] = EndPointDetection(wav_track_name, frame_size_msc, frame_overlap_msc, window_typy);

[y, Fs, bit] = wavread(wav_track_name);

 FrameSize=size(Frame_matrix)
 f = Frame_matrix;
 FourrierFrame=[];
 InversFM = [];
 for i=1:1:FrameSize(1)
     Frame_matrix(i,:) = fft(Frame_matrix(i,:));
     InversFM = cat(2, InversFM,ifft(Frame_matrix(i,:))); 
     Frame_matrix(i,:) = 20 * log(abs(Frame_matrix(i,:))+1);
 end
  FrameSize=size(Frame_matrix);
  Fmat=Frame_matrix(:,1:FrameSize(2)/2);
   figure ;
  subplot(2,1,1);
  Fmat = rot90(Fmat);
  [r c] = size(Fmat);
  newWidth = [1 5 * c];
  imshow(Fmat ,'Colormap',jet(256), 'XData', newWidth);
  
  subplot(2,1,2);
  specgram(y(:,1),256,Fs);
  
  figure ;
  
  F1 =[]
  [r c] = size(f);
  for i = 1 :r
    F1 = cat(2,F1, f(i,:));
  
  end
 
  subplot(3,1,1);
    plot(y);
 
  
 subplot(3,1,2);
    plot(F1);
 
 
 subplot(3,1,3);
 
   plot(InversFM);
  
  
end

