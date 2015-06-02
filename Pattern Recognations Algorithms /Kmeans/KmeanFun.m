function [  ] = KmeanFun( images, block_row, block_cul, K )

feature_matrix = Train( images, block_row, block_cul);
    [r1 c1] = size(feature_matrix);
  %  Mean = mean(feature_matrix (:,1:c1-1));
    
    [idx,C] = kmeans(feature_matrix(:,1:c1-1),K);
    
    for i=1 :r1
        s = [feature_matrix(i,c1) idx(i)];
       disp(s); 
    end
    
    

end

