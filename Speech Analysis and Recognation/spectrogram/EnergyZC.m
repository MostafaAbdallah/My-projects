function [ ZC , E, FrameMatrix ] = EnergyZC(wav_track_name, frame_size_msc, frame_overlap_msc, window_typy )
E=[];
count=0;
ZC=[];
FrameMatrix=Framing(wav_track_name, frame_size_msc, frame_overlap_msc, window_typy);
[y, Fs, bit] = wavread(wav_track_name);
[r c] = size(FrameMatrix);
for i=1:1:r
    count=0;
    v=FrameMatrix(i,:);
    vsquared=v.^2;
    energy=sum(vsquared);
    E=cat(1,E,energy);
    for j=1:1:length(v)
        if(j==length(v))
           num=v(j)*1;
        end
        if(j~=length(v))
       num=v(j)*v(j+1);
        end
       if(num<0)
           count=count+1;
       end
    end
    ZC=cat(1,ZC,count);
end
% subplot(2,2,1);
% plot(y);
% title('Original Wave');
% subplot(2,2,2);
% plot(FrameMatrix);
% title('frame matrix');
% subplot(2,2,3);
% plot(E');
% title('energy');
% subplot(2,2,4);
% plot(ZC');
% title('Zero Crossing');
end

