- 1.16: _Direct memory access_ is used for high-speed I/O devices in order to avoid increasing the
  CPU’s execution load.

  - (a) How does the CPU interface with the device to coordinate the transfer?

    The CPU coordinates the transfer with the device through control signals and memory-mapped I/O.

  - (b) How does the CPU know when the memory operations are complete?

    The CPU receives an interupt from the DMA controller when the operations are complete.

  - (c) The CPU is allowed to execute other programs while the DMA controller is transferring data.
    Does this process interfere with the execution of the user programs? If so, describe what forms
    of interference are caused.

    If the DMA controller and the CPU compete for access to the system bus, it can cause interference.

- 2.15: What are the two models of _interprocess communication_? What are the strengths and weakness
  of the two approaches?

  **Message Passing**

  - Strength: Offers built-in synchronization techniques.
  - Weakness: Incurs a higher performance overhead.

  **Shared Memory**

  - Strength: More efficient transfers for larger data.
  - Weakness: Prone to race conditions and requires synchronizations.

- 2.19: What is the main advantage of the _microkernel_ approach to system design? How do user
  programs and system services interact in a microkernel architecture? What are the disadvantages of
  using the microkernel approach?

  Advantages: Microkernels are more modular, different modules can swapped easily.

  Disadvantages: Performance can be harder to optimize due to context-switching and the modular
  design.

- 3.12: Describe the actions taken by a kernel to context-switch between processes.

  1. Save state into PCB1
  2. Reload state from PCB2
  3. Execute task until interupt or system call
  4. Save state into PCB2
  5. Reload state from PCB1

- 3.18: Give an example of a situation in which ordinary pipes are more suitable than named pipes
  and an example of a situation in which named pipes are more suitable than ordinary pipes.

  Ordinary pipes are suitable for simple one-to-one and one-way communications.

  Named pipes are suitable for complex many-to-many processes that are perhaps unrelated.
