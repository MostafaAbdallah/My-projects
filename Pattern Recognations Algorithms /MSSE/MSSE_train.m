function [  ] = MSSE_train( image ,block_row, block_cul )

    feature_matrix = Train(image ,block_row, block_cul );
    
    
    [r c] = size(feature_matrix);
    b = ones(r,1);
    z = [];
    W = [];
%=======================================================================    
    for L = 0 : 9
        z = [];
        w = [];
        for i=1 : r
            f = [];
            if(feature_matrix(i,c) == L)
                f = feature_matrix(i,1:c-1);
                f = cat(2,f,1);
                z = cat(1, z, f);      
            end
        end
    
        for i=1 : r
            if(feature_matrix(i,c) ~=L )
                f = feature_matrix(i,1:c-1);
                f = cat(2,f,1);
                z = cat(1, z, f * (-1));      
            end
        end
    
   
        w = inv(z' * z) * z' * b;
     
        w = cat(2, w', L);
        W = cat(1, W, w);
    end
     
%==========================================================================

save('w.mat','W');

end

