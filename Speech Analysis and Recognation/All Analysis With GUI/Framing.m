function [ Frame_matrix ,Frame_vector] = Framing(wav_track_name, frame_size_msc, frame_overlap_msc, window_typy)

[y, Fs, bit] = wavread(wav_track_name);
%wavplay(y, Fs);
Frame_matrix = [];
Frame_vector = [];

frame_size_sec = frame_size_msc / 1000;
frame_overlap_sec = frame_overlap_msc / 1000;

frame_size_samples = ceil(frame_size_sec * Fs);
frame_overlap_samples = ceil (frame_overlap_sec * Fs);

% disp(frame_size_samples);
% disp(frame_overlap_samples);

% 
% frame_size_samples = 20;
% frame_overlap_samples = 5;

[r, c] =  size(y);

%disp(r/20);

hamming_W = hamming(frame_size_samples);
hanning_W = hanning(frame_size_samples);
rectangle_w = rectwin(frame_size_samples);
[r1, c1] =  size(hamming_W);
%disp([r1, c1]);


count = 0;

for i = 1 : (frame_size_samples -frame_overlap_samples) : r
              
    if((i+frame_size_samples) > r) 
        limit = r;
        v = y(i:limit-1,1);
        v = padarray(v,[(i+frame_size_samples)-r 0], 'post');
        if(strcmp(window_typy, 'rectangle'))
            v = v .* 1;
        end  
        
        if(strcmp(window_typy, 'hamming'))
            v = v .* hamming_W;
        end 
        if(strcmp(window_typy, 'hanning'))
            v = v .* hanning_W;
        end 
            Frame_vector = cat(1,Frame_vector,v);
            Frame_matrix = cat(1,Frame_matrix, v');
   
        break;
        
    end
    
    if((i+frame_size_samples) <  r )
        
        limit = i+frame_size_samples;
     
    end
    
        if(i == 1)
            v = y(i:frame_size_samples,1);           
        end
        
        if(i ~= 1)
            v = y(i:limit-1,1);
        end
        
         if(strcmp(window_typy, 'rectangle'))
            v = v .* 1;
        end  
        
        if(strcmp(window_typy, 'hamming'))
            v = v .* hamming_W;
        end 
        if(strcmp(window_typy, 'hanning'))
            v = v .* hanning_W;
        end 
        
        Frame_vector = cat(1,Frame_vector,v);
        Frame_matrix = cat(1,Frame_matrix, v');
        count = count + 1;
        
%         if(count == 100)
%              break;
%         end
%        
    

end
figure;

 subplot(2,1,1);
 plot(y);
 title('Original Wave');
 subplot(2,1,2);
 plot((Frame_vector));
 title('Frame Matrix');
%wavplay(Frame_vector', frame_size_samples);
%disp(Frame_vector);


end

