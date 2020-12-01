use std::iter::FromIterator;
use std::collections::HashSet;
pub fn solve(input: String) -> String {
    let nums: Vec<u32> = input.split_whitespace().map(|x| x.parse().unwrap()).collect();
    let num_set: HashSet<u32> = HashSet::from_iter(nums.clone());

    let mut ans1 = 0;
    let mut ans2 = 0;
    for i in 0..nums.len() {
        if nums[i] > 2020 {
            continue;
        }
        for j in i+1..nums.len() {
            if nums[i] + nums[j] > 2020 {
                continue;
            }
            if nums[i] + nums[j] == 2020 {
                ans1 = nums[i] * nums[j];
            }
            if num_set.contains(&(2020 - nums[i] - nums[j])) {
                ans2 = nums[i] * nums[j] * (2020 - nums[i] - nums[j]);
            }
        }
        if ans1 > 0 && ans2 > 0 {
            break;
        }
    }

    format!("{}, {}", ans1, ans2)
}
