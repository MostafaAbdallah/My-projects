function [ ] = autoCor(wav_track_name, frame_size_msc, frame_overlap_msc, window_typy )
    
   FrameMatrix = EndPointDetection( wav_track_name, frame_size_msc, frame_overlap_msc, window_typy );
   [y, Fs, bit] = wavread(wav_track_name);   
   corr=xcorr(FrameMatrix(28,:));
   [r c]=size(corr);
   hFM=corr;
   corr2=xcorr(FrameMatrix(50,:));
   [r2 c2]=size(corr2);
   hFM2=corr2;
  
   [r c]=size(hFM);
   for i =1:c
       if(hFM(1,i) < 0)
           hFM(1,i) = 0;           
       end
   end
   [r c]=size(hFM);
    for i =1:c
       if(hFM2(1,i) < 0)
           hFM2(1,i) = 0;           
       end
   end
   
   
   figure;
   subplot(2,2,1);
   plot(FrameMatrix(28,:));
   title('Voiced Frame');
   subplot(2,2,2);
   plot(hFM);
   %title('AutoCorrelation for Voiced Frame');
   subplot(2,2,3);
   plot(FrameMatrix(50,:));
   title('Unvoiced Frame');
   subplot(2,2,4);
   plot(hFM2);
   title('AutoCerrelation for Unvoiced Frame');
   
   [r c]=size(hFM);
   hFM3=hFM;
   for i =1:c
       if(hFM(1,i) < 0.0020)
          % if(hFM(1,i) > -0.0020)
           hFM(1,i) = 0;
          % end
           
       end
   end
   
   figure;
   subplot(2,2,1);
   plot(FrameMatrix(28,:));
   title('Voiced Frame');
   subplot(2,2,2);
   plot(hFM3);
   title('AutoCorrelation for Voiced Frame');
   subplot(2,2,3);
   plot(hFM);
   title('AutoCorrelation after center clipping');
   
   
   
   %%%%%%%%%%%spectrogram%%%%%%%%%%
   
   VoicedFF=fft(FrameMatrix(20,:));
   VoicedFF=20*log(abs(VoicedFF)+1);
   [m n]=size(VoicedFF);
   %VoicedFF=VoicedFF(:,1:n/2);
   VoicedFF = imrotate(VoicedFF,90);
   figure;
   subplot(3,1,1);
   plot(FrameMatrix(28,:));
   title('Voiced Frame');
   subplot(3,1,2);
   plot(hFM);
   title('AutoCorrelation after center clipping');
   subplot(3,1,3);
   
  % imshow(VoicedFF); 
   specgram(VoicedFF,256,Fs);
   title('Spectrogram');
  %plot(VoicedFF);
end

