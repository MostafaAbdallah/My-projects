
function [ netTrained ] = NueralNetwork( images, block_row, block_cul,hiddenLayer)
    
    feature_matrix = Train( images, block_row, block_cul);
    feature_matrix  = feature_matrix';
    
    [r c] = size(feature_matrix);
    
    T = zeros(10, c);
    
    for i = 1 : c
        T(feature_matrix(r,i)+1, i) = 1;
        
    end
    
    net = newff(feature_matrix(1:r-1, :), T, hiddenLayer);
    netTrained = train(net, feature_matrix(1:r-1, :), T);
    
end

