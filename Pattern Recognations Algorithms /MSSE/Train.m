function [  feature_matrix ] = Train( images, block_row, block_cul  )
     
     feature_matrix =[];
     block_hight_Vector = [];
     block_widgth_Vector = [];
     feature_vector = [];

    for i = 1 : length(images)
   
        m = imread(images(i).name);
        m = im2bw(m);
        m = ~m;
        Box = regionprops(m, 'boundingbox');
        Box = struct2array(Box);
        m = imcrop(m,Box);
        [r, c] = size(m);
        
        
        if(mod(c, block_cul) ~= 0)
           m = padarray(m,[0 (block_cul - mod(c, block_cul))], 'post');
        
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
        
        feature_vector = [];
        %disp([r c]);
        
        for k=1:block_row
        for j=1:block_cul
        Centroid = regionprops(C{k, j}, 'Centroid');
       
        Centroid = struct2array(Centroid);
        if(isempty(Centroid))
              Centroid = [0 0]; 
                        
        end
            
       % disp(Centroid);
        Centroid = Centroid(1,1:2) ./ [r c]; 
        
        feature_vector = cat(2, feature_vector,Centroid);
        end
        end
        
        if(images(i).name(1) == '0')
            l = 0;
        end 
        if(images(i).name(1) == '1')
            l = 1;
        end
        if(images(i).name(1) == '2')
            l = 2;
        end
        if(images(i).name(1) == '3')
            l = 3;
        end
        if(images(i).name(1) == '4')
            l = 4;
        end
        if(images(i).name(1) == '5')
            l = 5;
        end
        if(images(i).name(1) == '6')
            l = 6;
        end
        if(images(i).name(1) == '7')
            l = 7;
        end
        if(images(i).name(1) == '8')
            l = 8;
        end
        if(images(i).name(1) == '9')
            l = 9;
        end
        
        disp(images(i).name(1));
        feature_vector = cat(2, feature_vector, l);
        feature_matrix = cat(1, feature_matrix, feature_vector);
        
       
      
    end
    
    

end

