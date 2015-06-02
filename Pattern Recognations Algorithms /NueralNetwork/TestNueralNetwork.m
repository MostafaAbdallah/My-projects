function [index] = TestNueralNetwork( image, block_row, block_cul, netTrained)

    feature_vector = Test( image, block_row, block_cul );
    
    feature_vector = feature_vector';
    
    V = sim(netTrained, feature_vector);
    disp(V);
    [m index] = max(V);
    index = index - 1;

end

