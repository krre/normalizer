<script lang="ts">
	import { onMount } from 'svelte';
	import init from '$lib/wasm/normalizer.js';

	const title = 'Normalizer';

	let device: string;

	onMount(() => {
		run();
	});

	async function run() {
		await init();
	}
</script>

<svelte:head>
	<title>{title}</title>
</svelte:head>
