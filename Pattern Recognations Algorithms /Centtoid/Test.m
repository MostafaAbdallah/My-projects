function [ Labal ] = Test( image, block_row, block_cul   )
        
    
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
        disp([r c]);
        
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
        
        disp(block_hight_Vector);
        disp(block_widgth_Vector);
        
        C = mat2cell(m,block_hight_Vector,block_widgth_Vector);
        
        
        for k=1:block_row
        for j=1:block_cul
            Centroid = regionprops(C{k, j}, 'Centroid');
       
            Centroid = struct2array(Centroid);
            if(isempty(Centroid))
                  Centroid = [0 0]; 
                        
            end
           
            Centroid = Centroid ./ [r c]; 
        
            feature_vector = cat(2, feature_vector,Centroid);
        end
        end
        
      
       FV = struct2array( load('fv'));
       
           
       [a b]= size(feature_vector);
       [r1 c1] = size(FV);
       for i = 1 : r1
            d = FV(i , 1: b);         
            f = cat(1, f, d);
               
       end
       
       for i = 1:2:b
         
          distances = distance('gc',feature_vector(:,i:i+1) ,f(:,i:i+1));
           dis = cat(2 , dis, distances);
       end
       [r1 c1] = size(dis);
       for i = 1 : r1
           t = 0;
       for j = 1 : c1
           
           t = t +(dis(i,j)^2);
           
           
       end
       total_distance = cat(1, total_distance, sqrt(t));
       end
      % disp(total_distance);
       index_labal = distances == min(distances);
       
       Labal = FV(index_labal, b+1);
       %FV = struct2array(FV.fv);   
      % disp(FV);
        

end

