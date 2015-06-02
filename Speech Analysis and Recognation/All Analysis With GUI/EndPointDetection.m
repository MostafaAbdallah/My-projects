function [ fv ] = EndPointDetection( wav_track_name, frame_size_msc, frame_overlap_msc, window_typy )

%FrameMatrix=Framing(wav_track_name, frame_size_msc, frame_overlap_msc, window_typy);

[ ZC , E , FrameMatrix] = EnergyZC(wav_track_name, frame_size_msc, frame_overlap_msc, window_typy );
[ Frame_matrix,Frame_vector]=Framing(wav_track_name, frame_size_msc, frame_overlap_msc, window_typy);
[y, Fs, bit] = wavread(wav_track_name);

frame_size_sec = 100/ 1000;
frame_size_samples = ceil(frame_size_sec * Fs);
[r c]=size(Frame_matrix);

count=0; % number of frames for first 100 msc

while(true)
    if(c>=frame_size_samples)
        break;
    end
    c = c + c;
    count = count + 1;
end

SubEnergy = E(1:count,:);
IMN = min(SubEnergy);
IMX = max(SubEnergy);

I2 = 4 + IMN;
I1 = 0.3 * (IMX-IMN)+IMN;

ITL = min(I1,I2);
ITU = 3 * ITL;


SubZC = ZC(1:count,:);

SZCRm = mean(SubZC);
SZCRstd = std(SubZC);

AVZC = mean(ZC);
V = 0.3 * (AVZC/SZCRm) + 0.7 * ((1 + SZCRstd)/SZCRm);

TZCRs = SZCRm + V * SZCRstd;

[r c]=size(E);

for i = 1 : r
   
       
  if(E(i) > ITU)
      N1 = i;
      break;
  end    
   

end

for i = r : -1: 1
      
  if(E(i) > ITU)
      N2 = i;
      break;
  end
end


[r c]=size(ZC);

for i = N1 : -1 : 1
   
       
  if(ZC(i) < TZCRs)
      N1 = i;
      break;
  end    
   

end

for i = N2 : r
      
  if(ZC(i) < TZCRs)
      N2 = i;
      break;
  end
end


  subplot(2,1,1);
 % frame_vector = FrameMatrix(:);
 fv=FrameMatrix(N1:N2,:);
  [r1 c1]=size(fv);
  FF=[];
  for i=1:1:r1
      FF=cat(2,FF,fv(i,:));
  end
  frame_vector = reshape (FrameMatrix, [], 1);
  plot(Frame_vector);
  title('frame matrix');
  subplot(2,1,2);
  
 % frame_vector = FrameMatrix(:);
    
  %frame_vector = reshape (FrameMatrix(N1:N2,:), [], 1);
  %fv=reshape(fv,1,[]);
  plot(FF);
title('After removing silence');


end

