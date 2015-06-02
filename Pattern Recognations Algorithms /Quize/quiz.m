function [  ] = quiz( x, L, fv )

L = L';    
[r c] = size(L);
[r1 c1] = size(x);
class1 = [];
class2 = [];
class3 = [];
for i = 1 :r
    if(L(i,1) == 1)
        class1 = cat(1, class1, x(i,1:c1));
    end
    if(L(i,1) == 2)
        class2 = cat(1, class2, x(i,1:c1));
    end
    if(L(i,1) == 3)
        class3 = cat(1, class3, x(i,1:c1));
    end
end
    
mean1 = class1;
mean2 = class2;
mean3 = class3;
[r c] = size(class1);
    if(r ~=1)
        mean1 = mean(class1);
    end
[r c] = size(class2);
    if(r ~=1)
        mean2 = mean(class2);
    end
[r c] = size(class3);
    if(r ~=1)
        mean3 = mean(class3);
    end
    dis = [];
    
   d = sqrt( (mean1(1,1) - fv(1,1))^2 + (mean1(1,2) - fv(1,3))^2 +(mean1(1,2) - fv(1,3))^2);
   dis = cat(1, dis,d);
   d = sqrt( (mean2(1,1) - fv(1,1))^2 + (mean2(1,2) - fv(1,3))^2 +(mean2(1,2) - fv(1,3))^2);
   %d =  distance('gc', mean2, fv);
   dis = cat(1, dis,d);
   d = sqrt( (mean3(1,1) - fv(1,1))^2 + (mean3(1,2) - fv(1,3))^2 +(mean3(1,2) - fv(1,3))^2);
   %d =  distance('gc', mean3, fv);
   dis = cat(1, dis,d);
   
   [m index] = min(dis);
   
   disp(index);

end

