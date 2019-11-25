
crc32:     file format elf64-x86-64


Disassembly of section .init:

00000000004003e0 <_init>:
  4003e0:	48 83 ec 08          	sub    $0x8,%rsp
  4003e4:	48 8b 05 0d 0c 20 00 	mov    0x200c0d(%rip),%rax        # 600ff8 <_DYNAMIC+0x1d0>
  4003eb:	48 85 c0             	test   %rax,%rax
  4003ee:	74 05                	je     4003f5 <_init+0x15>
  4003f0:	e8 3b 00 00 00       	callq  400430 <__gmon_start__@plt>
  4003f5:	48 83 c4 08          	add    $0x8,%rsp
  4003f9:	c3                   	retq   

Disassembly of section .plt:

0000000000400400 <printf@plt-0x10>:
  400400:	ff 35 02 0c 20 00    	pushq  0x200c02(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400406:	ff 25 04 0c 20 00    	jmpq   *0x200c04(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40040c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400410 <printf@plt>:
  400410:	ff 25 02 0c 20 00    	jmpq   *0x200c02(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400416:	68 00 00 00 00       	pushq  $0x0
  40041b:	e9 e0 ff ff ff       	jmpq   400400 <_init+0x20>

0000000000400420 <__libc_start_main@plt>:
  400420:	ff 25 fa 0b 20 00    	jmpq   *0x200bfa(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400426:	68 01 00 00 00       	pushq  $0x1
  40042b:	e9 d0 ff ff ff       	jmpq   400400 <_init+0x20>

0000000000400430 <__gmon_start__@plt>:
  400430:	ff 25 f2 0b 20 00    	jmpq   *0x200bf2(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  400436:	68 02 00 00 00       	pushq  $0x2
  40043b:	e9 c0 ff ff ff       	jmpq   400400 <_init+0x20>

Disassembly of section .text:

0000000000400440 <_start>:
  400440:	31 ed                	xor    %ebp,%ebp
  400442:	49 89 d1             	mov    %rdx,%r9
  400445:	5e                   	pop    %rsi
  400446:	48 89 e2             	mov    %rsp,%rdx
  400449:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40044d:	50                   	push   %rax
  40044e:	54                   	push   %rsp
  40044f:	49 c7 c0 f0 06 40 00 	mov    $0x4006f0,%r8
  400456:	48 c7 c1 80 06 40 00 	mov    $0x400680,%rcx
  40045d:	48 c7 c7 36 06 40 00 	mov    $0x400636,%rdi
  400464:	e8 b7 ff ff ff       	callq  400420 <__libc_start_main@plt>
  400469:	f4                   	hlt    
  40046a:	66 90                	xchg   %ax,%ax
  40046c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400470 <deregister_tm_clones>:
  400470:	b8 3f 10 60 00       	mov    $0x60103f,%eax
  400475:	55                   	push   %rbp
  400476:	48 2d 38 10 60 00    	sub    $0x601038,%rax
  40047c:	48 83 f8 0e          	cmp    $0xe,%rax
  400480:	48 89 e5             	mov    %rsp,%rbp
  400483:	77 02                	ja     400487 <deregister_tm_clones+0x17>
  400485:	5d                   	pop    %rbp
  400486:	c3                   	retq   
  400487:	b8 00 00 00 00       	mov    $0x0,%eax
  40048c:	48 85 c0             	test   %rax,%rax
  40048f:	74 f4                	je     400485 <deregister_tm_clones+0x15>
  400491:	5d                   	pop    %rbp
  400492:	bf 38 10 60 00       	mov    $0x601038,%edi
  400497:	ff e0                	jmpq   *%rax
  400499:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004004a0 <register_tm_clones>:
  4004a0:	b8 38 10 60 00       	mov    $0x601038,%eax
  4004a5:	55                   	push   %rbp
  4004a6:	48 2d 38 10 60 00    	sub    $0x601038,%rax
  4004ac:	48 c1 f8 03          	sar    $0x3,%rax
  4004b0:	48 89 e5             	mov    %rsp,%rbp
  4004b3:	48 89 c2             	mov    %rax,%rdx
  4004b6:	48 c1 ea 3f          	shr    $0x3f,%rdx
  4004ba:	48 01 d0             	add    %rdx,%rax
  4004bd:	48 d1 f8             	sar    %rax
  4004c0:	75 02                	jne    4004c4 <register_tm_clones+0x24>
  4004c2:	5d                   	pop    %rbp
  4004c3:	c3                   	retq   
  4004c4:	ba 00 00 00 00       	mov    $0x0,%edx
  4004c9:	48 85 d2             	test   %rdx,%rdx
  4004cc:	74 f4                	je     4004c2 <register_tm_clones+0x22>
  4004ce:	5d                   	pop    %rbp
  4004cf:	48 89 c6             	mov    %rax,%rsi
  4004d2:	bf 38 10 60 00       	mov    $0x601038,%edi
  4004d7:	ff e2                	jmpq   *%rdx
  4004d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004004e0 <__do_global_dtors_aux>:
  4004e0:	80 3d 59 0b 20 00 00 	cmpb   $0x0,0x200b59(%rip)        # 601040 <completed.6337>
  4004e7:	75 11                	jne    4004fa <__do_global_dtors_aux+0x1a>
  4004e9:	55                   	push   %rbp
  4004ea:	48 89 e5             	mov    %rsp,%rbp
  4004ed:	e8 7e ff ff ff       	callq  400470 <deregister_tm_clones>
  4004f2:	5d                   	pop    %rbp
  4004f3:	c6 05 46 0b 20 00 01 	movb   $0x1,0x200b46(%rip)        # 601040 <completed.6337>
  4004fa:	f3 c3                	repz retq 
  4004fc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400500 <frame_dummy>:
  400500:	48 83 3d 18 09 20 00 	cmpq   $0x0,0x200918(%rip)        # 600e20 <__JCR_END__>
  400507:	00 
  400508:	74 1e                	je     400528 <frame_dummy+0x28>
  40050a:	b8 00 00 00 00       	mov    $0x0,%eax
  40050f:	48 85 c0             	test   %rax,%rax
  400512:	74 14                	je     400528 <frame_dummy+0x28>
  400514:	55                   	push   %rbp
  400515:	bf 20 0e 60 00       	mov    $0x600e20,%edi
  40051a:	48 89 e5             	mov    %rsp,%rbp
  40051d:	ff d0                	callq  *%rax
  40051f:	5d                   	pop    %rbp
  400520:	e9 7b ff ff ff       	jmpq   4004a0 <register_tm_clones>
  400525:	0f 1f 00             	nopl   (%rax)
  400528:	e9 73 ff ff ff       	jmpq   4004a0 <register_tm_clones>
  40052d:	0f 1f 00             	nopl   (%rax)

0000000000400530 <InitTable>:
  400530:	55                   	push   %rbp
  400531:	48 89 e5             	mov    %rsp,%rbp
  400534:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  400538:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  40053f:	eb 52                	jmp    400593 <InitTable+0x63>
  400541:	8b 45 fc             	mov    -0x4(%rbp),%eax
  400544:	89 45 f4             	mov    %eax,-0xc(%rbp)
  400547:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
  40054e:	eb 20                	jmp    400570 <InitTable+0x40>
  400550:	8b 45 f4             	mov    -0xc(%rbp),%eax
  400553:	83 e0 01             	and    $0x1,%eax
  400556:	85 c0                	test   %eax,%eax
  400558:	74 0f                	je     400569 <InitTable+0x39>
  40055a:	8b 45 f4             	mov    -0xc(%rbp),%eax
  40055d:	d1 e8                	shr    %eax
  40055f:	35 20 83 b8 ed       	xor    $0xedb88320,%eax
  400564:	89 45 f4             	mov    %eax,-0xc(%rbp)
  400567:	eb 03                	jmp    40056c <InitTable+0x3c>
  400569:	d1 6d f4             	shrl   -0xc(%rbp)
  40056c:	83 45 f8 01          	addl   $0x1,-0x8(%rbp)
  400570:	83 7d f8 07          	cmpl   $0x7,-0x8(%rbp)
  400574:	7e da                	jle    400550 <InitTable+0x20>
  400576:	8b 45 fc             	mov    -0x4(%rbp),%eax
  400579:	48 98                	cltq   
  40057b:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
  400582:	00 
  400583:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  400587:	48 01 c2             	add    %rax,%rdx
  40058a:	8b 45 f4             	mov    -0xc(%rbp),%eax
  40058d:	89 02                	mov    %eax,(%rdx)
  40058f:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
  400593:	81 7d fc ff 00 00 00 	cmpl   $0xff,-0x4(%rbp)
  40059a:	7e a5                	jle    400541 <InitTable+0x11>
  40059c:	5d                   	pop    %rbp
  40059d:	c3                   	retq   

000000000040059e <CRC32>:
  40059e:	55                   	push   %rbp
  40059f:	48 89 e5             	mov    %rsp,%rbp
  4005a2:	48 83 ec 20          	sub    $0x20,%rsp
  /*pszBuffer保存到rbp-0x18处*/
  4005a6:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  /*ulLen保存到rbp-0x1c处*/	
  4005aa:	89 75 e4             	mov    %esi,-0x1c(%rbp)
  /*i = 0, rbp-0x4*/
  4005ad:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  4005b4:	8b 05 a6 0a 20 00    	mov    0x200aa6(%rip),%eax        # 601060 <bInit.2865>
  4005ba:	85 c0                	test   %eax,%eax
  4005bc:	75 14                	jne    4005d2 <CRC32+0x34>
  4005be:	bf 80 10 60 00       	mov    $0x601080,%edi
  4005c3:	e8 68 ff ff ff       	callq  400530 <InitTable>
  4005c8:	c7 05 8e 0a 20 00 01 	movl   $0x1,0x200a8e(%rip)        # 601060 <bInit.2865>
  4005cf:	00 00 00 
  /*ulRet = 0xFFFFFFFF*/
  4005d2:	c7 45 f4 ff ff ff ff 	movl   $0xffffffff,-0xc(%rbp)
  /*ulRet_wrong = 0xFFFFFFFF*/
  4005d9:	c7 45 f8 ff ff ff ff 	movl   $0xffffffff,-0x8(%rbp)
  4005e0:	eb 30                	jmp    400612 <CRC32+0x74>
  /*ulRet_wrong保存到eax*/
  4005e2:	8b 45 f8             	mov    -0x8(%rbp),%eax
  /*ulRet_wrong的最低字节赋值到edx,无符号扩展*/
  4005e5:	0f b6 d0             	movzbl %al,%edx
  /*i赋值给ecx*/
  4005e8:	8b 4d fc             	mov    -0x4(%rbp),%ecx
  /*pszBuffer赋值给rax*/
  4005eb:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  /*pszBuffer+i*/
  4005ef:	48 01 c8             	add    %rcx,%rax
  /*pszBuffer[i]赋值给eax，无符号扩展*/
  4005f2:	0f b6 00             	movzbl (%rax),%eax
  /*取最低字节赋值给eax,有符号扩展*/
  4005f5:	0f be c0             	movsbl %al,%eax
  /*index = (ulRet_wrong & 0xFF) ^ pszBuffer[i],但是此处pszBuffer[i]做了符号扩展*/
  4005f8:	31 d0                	xor    %edx,%eax
  /*eax有符号扩展为rax*/
  4005fa:	48 98                	cltq   
  /*aulTable+4*rax, rax如果作为正数是一个很大的数，此处也可以看做负数，总之此处可能会发生越界访问产生堆栈，也可能访问到的是垃圾数据*/
  4005fc:	8b 04 85 80 10 60 00 	mov    0x601080(,%rax,4),%eax
  /*ulRet_wrong赋值给edx*/
  400603:	8b 55 f8             	mov    -0x8(%rbp),%edx
  /*ulRet_wrong>>8*/
  400606:	c1 ea 08             	shr    $0x8,%edx
  /*(ulRet_wrong>>8)^aulTable[index]*/
  400609:	31 d0                	xor    %edx,%eax
  40060b:	89 45 f8             	mov    %eax,-0x8(%rbp)
  /*i+=1*/	
  40060e:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
  /*i赋值给eax*/	
  400612:	8b 45 fc             	mov    -0x4(%rbp),%eax
  /*i < ulLen*/
  400615:	3b 45 e4             	cmp    -0x1c(%rbp),%eax
  400618:	72 c8                	jb     4005e2 <CRC32+0x44>
  /*ulRet_wrong = ~ulRet_wrong*/
  40061a:	f7 55 f8             	notl   -0x8(%rbp)
  40061d:	8b 45 f8             	mov    -0x8(%rbp),%eax
  400620:	89 c6                	mov    %eax,%esi
  400622:	bf 10 07 40 00       	mov    $0x400710,%edi
  400627:	b8 00 00 00 00       	mov    $0x0,%eax
  40062c:	e8 df fd ff ff       	callq  400410 <printf@plt>
  400631:	8b 45 f4             	mov    -0xc(%rbp),%eax
  400634:	c9                   	leaveq 
  400635:	c3                   	retq   

0000000000400636 <main>:
  400636:	55                   	push   %rbp
  400637:	48 89 e5             	mov    %rsp,%rbp
  40063a:	48 83 ec 20          	sub    $0x20,%rsp
  40063e:	89 7d ec             	mov    %edi,-0x14(%rbp)
  400641:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
  400645:	c6 45 f0 31          	movb   $0x31,-0x10(%rbp)
  400649:	c6 45 f1 32          	movb   $0x32,-0xf(%rbp)
  40064d:	c6 45 f2 33          	movb   $0x33,-0xe(%rbp)
  400651:	c6 45 f3 e4          	movb   $0xe4,-0xd(%rbp)
  400655:	c6 45 f4 b8          	movb   $0xb8,-0xc(%rbp)
  400659:	c6 45 f5 9c          	movb   $0x9c,-0xb(%rbp)
  40065d:	c6 45 f6 31          	movb   $0x31,-0xa(%rbp)
  400661:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  400668:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
  40066c:	be 07 00 00 00       	mov    $0x7,%esi
  400671:	48 89 c7             	mov    %rax,%rdi
  400674:	e8 25 ff ff ff       	callq  40059e <CRC32>
  400679:	c9                   	leaveq 
  40067a:	c3                   	retq   
  40067b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400680 <__libc_csu_init>:
  400680:	41 57                	push   %r15
  400682:	41 89 ff             	mov    %edi,%r15d
  400685:	41 56                	push   %r14
  400687:	49 89 f6             	mov    %rsi,%r14
  40068a:	41 55                	push   %r13
  40068c:	49 89 d5             	mov    %rdx,%r13
  40068f:	41 54                	push   %r12
  400691:	4c 8d 25 78 07 20 00 	lea    0x200778(%rip),%r12        # 600e10 <__frame_dummy_init_array_entry>
  400698:	55                   	push   %rbp
  400699:	48 8d 2d 78 07 20 00 	lea    0x200778(%rip),%rbp        # 600e18 <__init_array_end>
  4006a0:	53                   	push   %rbx
  4006a1:	4c 29 e5             	sub    %r12,%rbp
  4006a4:	31 db                	xor    %ebx,%ebx
  4006a6:	48 c1 fd 03          	sar    $0x3,%rbp
  4006aa:	48 83 ec 08          	sub    $0x8,%rsp
  4006ae:	e8 2d fd ff ff       	callq  4003e0 <_init>
  4006b3:	48 85 ed             	test   %rbp,%rbp
  4006b6:	74 1e                	je     4006d6 <__libc_csu_init+0x56>
  4006b8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4006bf:	00 
  4006c0:	4c 89 ea             	mov    %r13,%rdx
  4006c3:	4c 89 f6             	mov    %r14,%rsi
  4006c6:	44 89 ff             	mov    %r15d,%edi
  4006c9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4006cd:	48 83 c3 01          	add    $0x1,%rbx
  4006d1:	48 39 eb             	cmp    %rbp,%rbx
  4006d4:	75 ea                	jne    4006c0 <__libc_csu_init+0x40>
  4006d6:	48 83 c4 08          	add    $0x8,%rsp
  4006da:	5b                   	pop    %rbx
  4006db:	5d                   	pop    %rbp
  4006dc:	41 5c                	pop    %r12
  4006de:	41 5d                	pop    %r13
  4006e0:	41 5e                	pop    %r14
  4006e2:	41 5f                	pop    %r15
  4006e4:	c3                   	retq   
  4006e5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  4006ec:	00 00 00 00 

00000000004006f0 <__libc_csu_fini>:
  4006f0:	f3 c3                	repz retq 
  4006f2:	66 90                	xchg   %ax,%ax

Disassembly of section .fini:

00000000004006f4 <_fini>:
  4006f4:	48 83 ec 08          	sub    $0x8,%rsp
  4006f8:	48 83 c4 08          	add    $0x8,%rsp
  4006fc:	c3                   	retq   
