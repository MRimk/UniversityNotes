---
title: Semester Research Project
---

<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029 MD034-->

## Description

Name:

>Effect of TCP BBR on existing localization algorithm

Our localization algorithm (see Background section) can localize differentiation against both UDP and TCP applications. But, as you have studied in the computer network course, there exists multiple versions of the TCP congestion control algorithm. So far, we have evaluated our algorithm using only one version which is TCP CUBIC. TCP CUBIC is a loss-based (i.e., window reacts to loss events) congestion control algorithm that is widely used in today’s Internet. However, little by little people are transitioning to a new algorithm which is TCP BBR (Bottleneck Bandwidth and RTT). TCP BBR is a rate-based congestion control algorithm. It tries to estimate a TCP’s flow share of the bottleneck bandwidth and regulate the sending rate accordingly. It is designed to avoid sending at high rates that can cause high loss rates and/or delays.

In this project, the student will assess the performance of our localization algorithm if we used TCP BBR instead of TCP Cubic. Specifically, the student will tackle the following questions:

- Does traffic still experience correlated loss trends when using TCP BBR?
- Is there a better metric than loss (e.g. throughput) that can be used to localize differentiation with TCP BBR?

To answer these questions, the student will design and run experiments, analyze results, and draw conclusions. Experiments will be conducted using emulation; that is, the Wehe servers and client will run on linux machines that we control. The client will be configured to perform differentiation. Therefore, students should be comfortable working on the OS level. As for the analysis, it can be done in any programming language the student desires (e.g., python, matlab).

This project is suitable for students interested in research. For a student to excel in this project, she/he needs to be comfortable with programming, basic statistics, and working with computer network problems (e.g., delay computation and TCP diagrams)
