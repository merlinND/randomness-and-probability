function visual_test()
	generators = {'oldrand-upper', 'oldrand-lower',... 
				'von-neumann', 'mersenne-twister', 'aes'};
	
	figure;
	clf;
	
	n = length(generators);
	data = csvread('../data/rand.csv', 2);
	
	for i = 1:n
		subplot(ceil(n/2), 2, i);
		hist(data(:, i));
		title(generators(i));
	end;
	
end