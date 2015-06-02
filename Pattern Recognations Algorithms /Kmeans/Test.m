function [ feature_vector] = Test( image, block_row, block_cul   )
        
    
     distances = [];
     f = [];
     block_hight_Vector = [];
     block_widgth_Vector = [];
     feature_vector = [];
     dis = [];
     total_distance = [];
        m = imread(image);
        m = im2bw(m);
        m = ~m;
        Box = regionprops(m, 'boundingbox');
        Box = struct2array(Box);
        m = imcrop(m,Box);
        [r c] = size(m);
       
        
        if(mod(c, block_cul) ~= 0)
           m = padarray(m,[0 (block_cul - mod(c, block_cul))], 'post');
           disp(size(m));
        
        end 
        if(mod(r, block_row) ~= 0)
           m = padarray(m,[(block_row - mod(r, block_row))  0], 'post');
        
        end    
        
        [r c] = size(m);
        block_hight = r/block_row;
        block_widgth = c/block_cul;
        block_hight_Vector = [];
        block_widgth_Vector = [];
       
        for j = 1 :block_row
            block_hight_Vector = cat(2 , block_hight_Vector,block_hight);
        end
        
        for j = 1 :block_cul
            block_widgth_Vector = cat(2 , block_widgth_Vector,block_widgth);
        end
        
        
        C = mat2cell(m,block_hight_Vector,block_widgth_Vector);
        
        
        for k=1:block_row
        for j=1:block_cul
            Centroid = regionprops(C{k, j}, 'Centroid');
       
            Centroid = struct2array(Centroid);
            if(isempty(Centroid))
                  Centroid = [0 0]; 
                        
            end
           
            Centroid = Centroid(1,1:2) ./ [r c]; 
        
            feature_vector = cat(2, feature_vector,Centroid);
        end
        end
        
      
     
end

