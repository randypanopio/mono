import numpy as np
import matplotlib.pyplot as plt
import textwrap
from matplotlib.ticker import LogLocator

pysort_sorted_array = [0.3597736358642578, 0.3762245178222656, 0.3972053527832031, 0.3573894500732422, 0.34999847412109375, 0.34427642822265625, 0.3533363342285156, 0.3535747528076172, 0.36334991455078125, 0.3452301025390625, 0.35071372985839844, 0.3535747528076172, 0.3428459167480469, 0.35762786865234375, 0.3666877746582031, 0.3554821014404297, 0.34999847412109375, 0.3376007080078125, 0.34117698669433594, 0.3654956817626953, 0.3612041473388672, 0.34546852111816406, 0.3421306610107422, 0.34427642822265625, 0.3647804260253906, 0.35643577575683594, 0.3571510314941406, 0.3485679626464844, 0.3635883331298828, 0.35381317138671875, 0.3466606140136719, 0.3459453582763672]

pysort_rev_sort_array = [0.3533363342285156, 0.3497600555419922, 0.34236907958984375, 0.34999847412109375, 0.3418922424316406, 0.34809112548828125, 0.3654956817626953, 0.3478527069091797, 0.34809112548828125, 0.33855438232421875, 0.3418922424316406, 0.34427642822265625, 0.33783912658691406, 0.3371238708496094, 0.33664703369140625, 0.34618377685546875, 0.34427642822265625, 0.3402233123779297, 0.3428459167480469, 0.33974647521972656, 0.34499168395996094, 0.3364086151123047, 0.3457069396972656, 0.34236907958984375, 0.33974647521972656, 0.3428459167480469, 0.3485679626464844, 0.3514289855957031, 0.3485679626464844, 0.3447532653808594, 0.3407001495361328, 0.3509521484375]

pysort_random_array = [0.3535747528076172, 0.3516674041748047, 0.3573894500732422, 0.3521442413330078, 0.35452842712402344, 0.3533363342285156, 0.3521442413330078, 0.35691261291503906, 0.3685951232910156, 0.35643577575683594, 0.3600120544433594, 0.35572052001953125, 0.35190582275390625, 0.3726482391357422, 0.3650188446044922, 0.3578662872314453, 0.3566741943359375, 0.35858154296875, 0.36716461181640625, 0.3561973571777344, 0.35309791564941406, 0.3540515899658203, 0.35119056701660156, 0.35953521728515625, 0.3559589385986328, 0.3509521484375, 0.3592967987060547, 0.3552436828613281, 0.3542900085449219, 0.35572052001953125, 0.3688335418701172, 0.3707408905029297]


tim_sorted_array =[0.135900, 0.131900, 0.136500, 0.137200, 0.150800, 0.136700, 0.136400, 0.149600, 0.136600, 0.142200, 0.132600, 0.136900, 0.136600, 0.136400, 0.135900, 0.136900, 0.137000, 0.136700, 0.136700, 0.136600, 0.136200, 0.136200, 0.136000, 0.136000, 0.136500, 0.136100, 0.136000, 0.135900, 0.132400, 0.136100, 0.131100, 0.135900]

tim_rev_sort_array = [0.167700, 0.167500, 0.166900, 0.167300, 0.167400, 0.167300, 0.174500, 0.167700, 0.167300, 0.167000, 0.166900, 0.167400, 0.166900, 0.167000, 0.166800, 0.166800, 0.166800, 0.166800, 0.167300, 0.170300, 0.165900, 0.165700, 0.166100, 0.170500, 0.166000, 0.166200, 0.166000, 0.171200, 0.167400, 0.168400, 0.168300, 0.167200]

tim_random_array = [7.049800, 7.561700, 7.048700, 7.054500, 6.982700, 7.257900, 6.998700, 7.075700, 6.998400, 7.064900, 7.156200, 7.033000, 7.111200, 7.126300, 7.043200, 7.120000, 7.048600, 7.146000, 7.028600, 7.114300, 7.062400, 7.113300, 7.083700, 7.187500, 7.122100, 7.113300, 7.071500, 7.069400, 7.191000, 7.031000, 7.045900, 7.021300]

merge_sorted_array =[3.806500, 3.825300, 3.903800, 3.814300, 3.845000, 3.841100, 3.834800, 3.839600, 3.823700, 3.849700, 3.852100, 3.920200, 3.819800, 3.872700, 3.849500, 3.897000, 3.892500, 3.848100, 3.814000, 3.897800, 3.850900, 3.823700, 3.798200, 3.820300, 3.821600, 3.810100, 3.819000, 3.987500, 3.828500, 3.808700, 3.781300, 3.856400]

merge_rev_sort_array = [3.890100, 4.272500, 3.756900, 3.857500, 3.839200, 3.820100, 3.808400, 3.777800, 3.810500, 4.282900, 3.902800, 3.821000, 3.857300, 3.841600, 3.826800, 3.854500, 3.832200, 3.803000, 3.905000, 3.806800, 3.842500, 3.797200, 3.872800, 3.879100, 3.830900, 3.801300, 3.852700, 3.806300, 3.816500, 3.804400, 3.852700, 3.809500]

merge_random_array = [6.910200, 6.934300, 7.045000, 6.906500, 6.931000, 6.938700, 6.977100, 6.905200, 6.915700, 7.074800, 7.220400, 6.941300, 6.897500, 6.929600, 7.019600, 7.055400, 6.933700, 6.886500, 6.929100, 6.889100, 6.970300, 6.918100, 6.989300, 6.890200, 6.978100, 6.924800, 6.922900, 6.908000, 6.928000, 7.038000, 6.915000, 6.921400]

insertion_sorted_array =[0.113500, 0.113300, 0.113400, 0.118100, 0.114200, 0.114000, 0.114100, 0.114100, 0.114500, 0.118200, 0.114000, 0.114200, 0.114100, 0.114000, 0.117600, 0.114100, 0.114000, 0.114100, 0.114000, 0.114100, 0.118700, 0.114000, 0.114100, 0.114000, 0.114100, 0.114100, 0.114200, 0.114100, 0.114100, 0.114000, 0.114000, 0.119800]

insertion_rev_sort_array = [2903.804100, 2906.046000, 2887.440100, 2906.567800, 2923.457100, 2891.270400, 2904.349000, 2907.429300, 2908.061300, 2897.125900, 2902.056900, 2907.312300, 2915.082300, 2900.143100, 2908.600900, 2912.958300, 2893.540600, 2900.206400, 2919.883100, 2924.844900, 2918.956900, 2904.944400, 2916.460600, 2902.321500, 2928.602000, 2925.750100, 2921.396100, 2910.620300, 2893.219800, 2909.548700, 2940.139200, 2919.661700]

insertion_random_array = [1454.666100, 1446.270300, 1461.054100, 1454.153700, 1454.203700, 1455.004300, 1459.403900, 1463.500000, 1462.761700, 1469.455400, 1465.414300, 1463.570100, 1453.514100, 1449.975000, 1448.871700, 1448.102800, 1459.917100, 1455.108600, 1448.544700, 1463.500900, 1458.828600, 1452.458400, 1459.951200, 1451.425600, 1439.260300, 1450.511100, 1451.656100, 1458.943900, 1467.928300, 1457.654600, 1445.852500, 1467.533300]

# one graph
tim_sorted_meantime = np.mean(tim_sorted_array)
tim_sorted_deviation = np.std(tim_sorted_array)
tim_rev_sort_meantime = np.mean(tim_rev_sort_array)
tim_rev_sort_deviation = np.std(tim_rev_sort_array)
tim_random_meantime = np.mean(tim_random_array)
tim_random_deviation = np.std(tim_random_array)


# 2nd graph
merge_sorted_meantime = np.mean(merge_sorted_array)
merge_sorted_deviation = np.std(merge_sorted_array)
merge_rev_sort_meantime = np.mean(merge_rev_sort_array)
merge_rev_sort_deviation = np.std(merge_rev_sort_array)
merge_random_meantime = np.mean(merge_random_array)
merge_random_deviation = np.std(merge_random_array)


# 3rd graph
insertion_sorted_meantime = np.mean(insertion_sorted_array)
insertion_sorted_deviation = np.std(insertion_sorted_array)
insertion_rev_sort_meantime = np.mean(insertion_rev_sort_array)
insertion_rev_sort_deviation = np.std(insertion_rev_sort_array)
insertion_random_meantime = np.mean(insertion_random_array)
insertion_random_deviation = np.std(insertion_random_array)

# 4th graph
pysort_sorted_meantime = np.mean(pysort_sorted_array)
pysort_sorted_deviation = np.std(pysort_sorted_array)
pysort_rev_sort_meantime = np.mean(pysort_rev_sort_array)
pysort_rev_sort_deviation = np.std(pysort_rev_sort_array)
pysort_random_meantime = np.mean(pysort_random_array)
pysort_random_deviation = np.std(pysort_random_array)


print(f"tim_sorted_meantime: {tim_sorted_meantime}, tim_sorted_deviation: {tim_sorted_deviation}")
print(f"tim_rev_sort_meantime: {tim_rev_sort_meantime}, tim_rev_sort_deviation: {tim_rev_sort_deviation}")
print(f"tim_random_meantime: {tim_random_meantime}, tim_random_deviation: {tim_random_deviation}")
print(f"merge_sorted_meantime: {merge_sorted_meantime}, merge_sorted_deviation: {merge_sorted_deviation}")
print(f"merge_rev_sort_meantime: {merge_rev_sort_meantime}, merge_rev_sort_deviation: {merge_rev_sort_deviation}")
print(f"merge_random_meantime: {merge_random_meantime}, merge_random_deviation: {merge_random_deviation}")
print(f"insertion_sorted_meantime: {insertion_sorted_meantime}, insertion_sorted_deviation: {insertion_sorted_deviation}")
print(f"insertion_rev_sort_meantime: {insertion_rev_sort_meantime}, insertion_rev_sort_deviation: {insertion_rev_sort_deviation}")
print(f"insertion_random_meantime: {insertion_random_meantime}, insertion_random_deviation: {insertion_random_deviation}")

c1 = '#F5DD90'
c2 = '#F68E5F'
c3 = '#586BA4'
c4 = '#F76C5E'
c_out = '#664147'
labels = ['Sorted', 'Reverse Sorted', 'Random']

pysort_means = [pysort_sorted_meantime, pysort_rev_sort_meantime, pysort_random_meantime]
pysort_devs = [pysort_sorted_deviation, pysort_rev_sort_deviation, pysort_random_deviation]

tim_means = [tim_sorted_meantime, tim_rev_sort_meantime, tim_random_meantime]
tim_devs = [tim_sorted_deviation, tim_rev_sort_deviation, tim_random_deviation]

merge_means = [merge_sorted_meantime, merge_rev_sort_meantime, merge_random_meantime]
merge_devs = [merge_sorted_deviation, merge_rev_sort_deviation, merge_random_deviation]

insertion_means = [insertion_sorted_meantime, insertion_rev_sort_meantime, insertion_random_meantime]
insertion_devs = [insertion_sorted_deviation, insertion_rev_sort_deviation, insertion_random_deviation]

x = np.arange(len(labels))  # the label locations
width = 0.2  # the width of the bars
fig, ax = plt.subplots(figsize=(10, 6))  # Keep your desired figsize

# Move grid lines to the back and add evenly spaced horizontal lines
ax.set_axisbelow(True)  # Move the grid lines to the back
ax.yaxis.grid(True, linestyle='solid', linewidth=0.5)
ax.yaxis.set_major_locator(LogLocator(base=10, numticks=5))

fig.subplots_adjust(hspace=0.5)  # Adjust the top padding (value < 1)
rects1 = ax.bar(x - 1.5 * width, pysort_means, width, yerr=pysort_devs, label='Python Sort', color=c_out)
rects2 = ax.bar(x - 0.5 * width, tim_means, width, yerr=tim_devs, label='C Tim Sort', color=c1)
rects3 = ax.bar(x + 0.5 * width, merge_means, width, yerr=merge_devs, label='C Merge Sort', color=c2)
rects4 = ax.bar(x + 1.5 * width, insertion_means, width, yerr=insertion_devs, label='C Insertion Sort', color=c3)

# Add some text for labels, title and custom x-axis tick labels, etc.
ax.set_xlabel('Array Type', fontweight='bold')
ax.set_ylabel('Time (ms)', fontweight='bold')
ax.set_title('Sort Times by Array Type and Sort Algorithm')
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.set_yscale('log')
ax.legend()

ax.margins(y=0.2)  # Add margin to the top (and bottom) of the graph

# Function to add annotations with standard deviation margins and wrap text to fit bar width
def autolabel(rects, std_devs):
    """Attach a text label above each bar in *rects*, displaying its height with standard deviation."""
    for rect, std_dev in zip(rects, std_devs):
        height = rect.get_height()
        label = f'{height:.2f}±{std_dev:.2f} ms'
        wrapped_label = '\n'.join(textwrap.wrap(label, width=6))
        ax.annotate(wrapped_label,
                    xy=(rect.get_x() + rect.get_width() / 2, height),
                    xytext=(0, 8),  # Offset to avoid clipping
                    textcoords="offset points",
                    ha='center', va='bottom')

autolabel(rects1, pysort_devs)
autolabel(rects2, tim_devs)
autolabel(rects3, merge_devs)
autolabel(rects4, insertion_devs)

fig.tight_layout()

plt.savefig('sort_times.png')


# TODO generate graphs for my branch analyses