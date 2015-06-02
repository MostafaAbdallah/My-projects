function [ Labal ] = MSSE_test( image, block_row, block_cul)
    
    feature_vector = Test( image, block_row, block_cul);
    feature_vector = cat(2,feature_vector , 1);
    
    W = struct2array( load('W'));
    
    count = 0;
    
    [r c] = size(W);
    
    for i = 1:r
        
        d = W(i,1:c-1) * feature_vector';
        
        if(d > 0)
            count = count +1;
            Labal = W(i,c);
        end
        
        disp(d);
        disp(W(i,c));
        
    end
    
    if(count == 0)
        disp('new class');
        Labal = -1;
    end
    if(count == 2)
        disp('undifined');
        Labal = -1;
    end

end

