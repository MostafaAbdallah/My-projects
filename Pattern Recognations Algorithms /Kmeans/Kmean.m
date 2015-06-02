function [  ] = Kmean(images, block_row, block_cul, K)

    feature_matrix = Train( images, block_row, block_cul);
    [r1 c1] = size(feature_matrix);
    Mean = mean(feature_matrix (:,1:c1-1));
    
    
    [r c] = size(Mean);
    
    while r < K
        temp = Mean;
        Mean = [];
        for i =1 : r
            Mean = cat(1, Mean, temp(i,:)-1); 
            Mean = cat(1, Mean, temp(i,:)+1);
            
        end
        [r c] = size(Mean);
        sort_M = [];
        for j =1 : r1
            Dis = [];
            for q = 1 : r
                d = pdist2( feature_matrix(j,1:c1-1),Mean(q,:));
                Dis = cat(1,Dis,d);
                
            end
            [MIN index] = min(Dis);
            M = [index j];
            sort_M = cat(1,sort_M, M);
        end
        counter = zeros(r,1);
        Mean = zeros(r,c);
        for i=1:r1
            s = feature_matrix(j,1:c1-1);
           Mean(sort_M(i,1),:) = Mean(sort_M(i,1),:) + feature_matrix(j,1:c1-1);
           counter(sort_M(i,1),:) = counter(sort_M(i,1),:) + 1;  
        
        end
        
        for i=1 : r
            Mean(i,:) = Mean(i,:) ./counter(i,1);
        end
        
        
    end
    
    
      
    for K =0 : 10
        
        [r c] = size(Mean);
        sort_M = [];
        for j =1 : r1
            Dis = [];
            for q = 1 : r
                d = pdist2( feature_matrix(j,1:c1-1),Mean(q,:));
                Dis = cat(1,Dis,d);
                
            end
            [MIN index] = min(Dis);
            M = [index j feature_matrix(j,c1)];
            sort_M = cat(1,sort_M, M);
        end
        counter = zeros(r,1);
        Mean = zeros(r,c);
        for i=1:r1
            s = feature_matrix(j,1:c1-1);
           Mean(sort_M(i,1),:) = Mean(sort_M(i,1),:) + feature_matrix(j,1:c1-1);
           counter(sort_M(i,1),:) = counter(sort_M(i,1),:) + 1;  
        
        end
        
        for i=1 : r
            Mean(i,:) = Mean(i,:) ./counter(i,1);
        end
        
    
    end
    
    
    [r c] = size(sort_M);
    for i=1 :r
        s = [sort_M(i,1) sort_M(i,3)];
       disp(s); 
    end
    
    
    
    
    
    
    

end

