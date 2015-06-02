function [] = PCA( image, block_row, block_cul)

 m = imread(image); 

 feature_vector = [];
 
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
     
     for i=1:block_row
        for j=1:block_cul
        
         block = C{i,j};
         f = block(:);
         
         
         feature_vector = cat(2, feature_vector, f);
     
        end
     end
     
     Mean = mean(feature_vector');
     Mean = Mean';
 
     [r c] = size(feature_vector);
     feature_vector = im2double(feature_vector);
     for i = 1 : c
        feature_vector(:,i) = feature_vector(:,i) - Mean; 
     end
     
     COV = cov(feature_vector');
     
     [egin_vector egin_value] = eig(COV);
     E_value= diag(egin_value);
     
    % [B IM] = sort(E_value);
     
     %disp(egin_vectorm);
     
     Final = []; 
     
     [r c] = size(feature_vector);
     for i = 1 : c
        f = egin_vector * feature_vector(:,i);
        Final = cat(2, Final, f);
     end
     
     [r c] = size(feature_vector);
     for i = 1 : c
        
        Final(r-20:r,i) = 0;
     end
     InverseFinal = [];
     [r c] = size(Final);
     for i = 1 : c
        f = egin_vector' * Final(:,i);
        InverseFinal = cat(2, InverseFinal, f);
     end
     
     for i = 1 : c
        InverseFinal(:,i) = InverseFinal(:,i) + Mean;
        
     end
     InverseFinal = uint8(InverseFinal);
    % m = imread(image);
     [Row col] = size(m);
     count = 1;
     new_m = [];
     R = [];
    for i=1:block_row
        R = [];
        for j=1:block_cul
        
        n = reshape(InverseFinal(:,count), [block_hight  block_widgth]);
        R = cat(2, R, n);
        count = count + 1;
        end
        new_m = cat(1, new_m, R);
     end
     subplot(2,1,1);
      
     imshow(m);
     subplot(2,1,2);
     
     imshow(uint8(new_m));
    
     
     
     

end

