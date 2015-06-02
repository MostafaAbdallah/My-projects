function [ FV ] = histgram( image )
    
    m = imread(image);
    [r c] = size(m);
    
     if(mod(c, 2) ~= 0)
           m = padarray(m,[0 (2 - mod(c, 2))], 'post');
        
     end 
    if(mod(r, 2) ~= 0)
           m = padarray(m,[(2- mod(r, 2))  0], 'post');
        
    end    
        
    block_hight = r/2;
    block_widgth = c/2;t
    imshow(m);
        C = mat2cell(m,[block_hight block_hight],[block_widgth block_widgth]);
        
        FV = [];
        
        for i = 1: 2
            for j = 1: 2
                his = zeros(256,1);
               % disp(C{i, j});
                mat = C{i, j};
                for k = 1: block_hight
                   for l = 1: block_widgth
                        his((mat(k,l) + 1 ), 1) = his(mat(k,l), 1) + 1; 
                    end
                    
                end
                    FV = cat(1,FV,his);
                
            end
        
        end
        
        
        

end

