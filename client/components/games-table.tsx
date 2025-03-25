"use client";

import {
    Table,
    TableBody, TableCaption,
    TableCell,
    TableHead,
    TableHeader,
    TableRow,
} from "@/components/ui/table"
import {Badge} from "@/components/ui/badge"
import {ScrollArea} from "@/components/ui/scroll-area";
import {Button} from "@/components/ui/button";

export type Game = {
    id: string
    owner: string
    status: "waiting" | "playing" | "ended"
}

// Définition des colonnes avant l'utilisation
function renderStatus(game: Game) {
    // Typage explicite des variantes
    const statusColors: Record<Game["status"], "success" | "warning" | "destructive"> = {
        waiting: "success",
        playing: "warning",
        ended: "destructive",
    };

    const statusDisplayName: Record<Game["status"], string> = {
        waiting: "En attente de joueurs",
        playing: "Partie en cours",
        ended: "Partie terminée",
    }

    return (
        <Badge variant={statusColors[game.status]} className="rounded-full">
            {statusDisplayName[game.status]}
        </Badge>
    );
}

export function GamesTable({games}: { games: Game[] }) {
    return (
        <div className="rounded-md border">
            <ScrollArea className={"max-h-72 overflow-y-auto"}>
                <Table>
                    <TableHeader>
                        <TableRow>
                            <TableHead className="w-[100px]">Code</TableHead>
                            <TableHead>Créateur</TableHead>
                            <TableHead>Status</TableHead>
                            {games.length ? (
                                <TableHead className="text-right"></TableHead>
                            ) : <></>}
                        </TableRow>
                    </TableHeader>
                    <TableBody>
                        {games.length ? (
                            games.map((game) => (
                                <TableRow key={game.id}>
                                    <TableCell className="font-medium">{game.id}</TableCell>
                                    <TableCell>{game.owner}</TableCell>
                                    <TableCell>{
                                        renderStatus(game)
                                    }</TableCell>
                                    <TableCell className="text-right">
                                        <Button variant={"outline"} className={"cursor-pointer"}>Rejoindre</Button>
                                    </TableCell>
                                </TableRow>
                            ))
                        ) : (
                            <TableRow>
                                <TableCell colSpan={4} className="h-24 text-center">Aucune partie trouvée</TableCell>
                            </TableRow>
                        )}
                    </TableBody>
                </Table>
            </ScrollArea>
        </div>
    );
}
